#include "board.h"

// #define PLUS std::plus<int>
// #define MINUS std::minus<int>

Board::Board(Camera* camera)
{
  this->camera = camera;
  Init();
}

Board::~Board()
{
}

void Board::Init()
{
  modelManager = new ModelManager();
  modelManager->LoadAllModels();
  modelManager->LoadTextures();
  selectedPiece = NULL;
  whiteToMove = true;
  show2dBoard = false;
  boardState = STANDARD;
  
  // Initialize pieces.
  int x, y;
  // Pawns and empty squares.
  for (x = 0; x < 8; x++)
  {
    pieces[x][1] = new Piece(PAWN, WHITE, modelManager);
    pieces[x][6] = new Piece(PAWN, BLACK, modelManager);
    for (y = 2; y < 6; y++)
    {
      pieces[x][y] = new Piece(EMPTY);
    }
  }
  
  // Back rows.
  for (x = 0; x < 8; x++)
  {
    if (x == 0 || x == 7)
    {
      pieces[x][0] = new Piece(CASTLE, WHITE, modelManager);
      pieces[x][7] = new Piece(CASTLE, BLACK, modelManager);
    }
    else if (x == 1 || x == 6)
    {
      pieces[x][0] = new Piece(KNIGHT, WHITE, modelManager);
      pieces[x][7] = new Piece(KNIGHT, BLACK, modelManager);
    }
    else if (x == 2 || x == 5)
    {
      pieces[x][0] = new Piece(BISHOP, WHITE, modelManager);
      pieces[x][7] = new Piece(BISHOP, BLACK, modelManager);
    }
  }

  pieces[4][0] = new Piece(KING, WHITE, modelManager);
  pieces[4][7] = new Piece(KING, BLACK, modelManager);
  pieces[3][0] = new Piece(QUEEN, WHITE, modelManager);
  pieces[3][7] = new Piece(QUEEN, BLACK, modelManager);
}

// TODO: Move these functions elsewhere.
int Add(int i, int j)
{
  return i + j;
}

int Sub(int i, int j)
{
  return i - j;
}

int Id(int i, int j)
{
  return i;
}

bool Board::IsWhiteToMove()
{
  return whiteToMove;
}

void Board::Toggle2dMode()
{
  show2dBoard = !show2dBoard;
}

BoardState Board::GetBoardState()
{
  return boardState;
}

void Board::Draw()
{
  int i, j;

  // Draw board base.
  glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.0, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 8*SQUARE_SIZE, -0.01);
    glVertex3f(0.0, 8*SQUARE_SIZE, -0.01);
  glEnd();

  // Draw pieces and squares (3D).
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j]->Draw(i, j);
    }
  }

  if (show2dBoard)
  {
    // Draw pieces and squares (2D).
    OpenGLUtil::StartOrtho();
    for (i = 0; i < 8; i++)
    {
      for (j = 0; j < 8; j++)
      {
        pieces[i][j]->Draw2D(i, j);
      }
    }

    OpenGLUtil::EndOrtho();
  }
}

void Board::EnableSelectionMode(bool enable)
{
  int i, j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (enable) 
  {
    glDisable(GL_LIGHTING);
  }
  else
  { 
    glEnable(GL_LIGHTING);
  }

  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j]->EnableSelectionMode(enable, i, j);
    }
  }
}

void Board::SetSelectedPiece(int i, int j)
{
  selectedPiece = pieces[i][j];
  selectedPiece->SetSelected(true);
  selCoord[0] = i;
  selCoord[1] = j;
  
  // Only highlight possible moves if correct turn.
  PieceColour selCol = selectedPiece->GetColour();
  if ((selCol == WHITE && whiteToMove) || (selCol == BLACK && !whiteToMove))
  {
    HighlightPossibleMoves();
  }
}

void Board::MoveSelectedPiece(int i, int j)
{  
  pieces[i][j] = selectedPiece;
  pieces[selCoord[0]][selCoord[1]] = new Piece(EMPTY);

  // Switch turns
  selectedPiece->SetHasMoved();
  selectedPiece = NULL;
  whiteToMove = !whiteToMove;
  camera->RotateToWhite(whiteToMove);

  // After move calculate board state i.e. see if anyone in in check, stalemate or checkmate.
  boardState = IsInCheck(whiteToMove ? WHITE : BLACK, 0) ? CHECK : STANDARD;
}

void Board::SelectSquareAt(int x, int y)
{
  GLfloat rgb[4];
  int i, j;
  EnableSelectionMode(true);
  glReadBuffer(GL_BACK);
  glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, rgb);
  
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if (pieces[i][j]->CheckIfClicked(x, y, rgb, show2dBoard))
      {
        PieceState stateOfClickedPiece = pieces[i][j]->GetState();
        UnhighlightPieces();
        switch (stateOfClickedPiece)
        {
          case NORMAL:
            SetSelectedPiece(i, j);
            break;
          case HIGHLIGHTED:
            MoveSelectedPiece(i, j);
            break;
          case SELECTED:
            selectedPiece = NULL;
            break;
        }     
        goto end_loop;
      }
    }
  }
  // If click did not select a piece/square then return.
  UnhighlightPieces();

  end_loop:
    EnableSelectionMode(false);
}

void Board::HighlightPossibleMoves()
{
  vector<Coord> moves = GetPossibleMoves(Coord(selCoord[0], selCoord[1]), 0);

  for (vector<Coord>::iterator it = moves.begin(); it != moves.end(); ++it)
  {
    Coord m = *it;
    pieces[m.x][m.y]->SetHighlighted(true);
  }
}

// Gets the possible moves for the piece at (i, j) as a vector of coords.
vector<Coord> Board::GetPossibleMoves(Coord p, int l)
{
  vector<Coord>* moves = new vector<Coord>();
  if (p.OutOfRange()) return *moves;

  Piece* piece = pieces[p.x][p.y];
  if (piece == NULL) return *moves;
  PieceColour col = piece->GetColour();
  int x = p.x;
  int y = p.y;
  int i = (col == WHITE) ? 1 : -1;

  switch (piece->GetType())
  {
    case EMPTY: return *moves;
    case PAWN:    
      if (SafeAddMovePawn(p, Coord(x, y+i), moves, l)
        && ((y == 1 && col == WHITE) || (y == 6 && col == BLACK)))
      {
        // Pawns can move 2 squares only from start position
        SafeAddMovePawn(p, Coord(x, y+2*i), moves, l);
      }

      // Pawns take diagonally
      SafeAddMovePawnTake(p, Coord(x+1, y+i), col, moves, l);
      SafeAddMovePawnTake(p, Coord(x-1, y+i), col, moves, l);

      //TODO: en passent case
      break;
    case KNIGHT:
      SafeAddMove(p, Coord(x+1, y+2), col, moves, l);
      SafeAddMove(p, Coord(x+1, y-2), col, moves, l);
      SafeAddMove(p, Coord(x-1, y+2), col, moves, l);
      SafeAddMove(p, Coord(x-1, y-2), col, moves, l);
      SafeAddMove(p, Coord(x+2, y+1), col, moves, l);
      SafeAddMove(p, Coord(x+2, y-1), col, moves, l);
      SafeAddMove(p, Coord(x-2, y+1), col, moves, l);
      SafeAddMove(p, Coord(x-2, y-1), col, moves, l);
      break;
    case BISHOP:
      SafeAddMoves(p, &Add, &Add, col, moves, l);
      SafeAddMoves(p, &Add, &Sub, col, moves, l);
      SafeAddMoves(p, &Sub, &Add, col, moves, l);
      SafeAddMoves(p, &Sub, &Sub, col, moves, l);
      break;
    case CASTLE:
      SafeAddMoves(p, &Id, &Add, col, moves, l);
      SafeAddMoves(p, &Id, &Sub, col, moves, l);
      SafeAddMoves(p, &Add, &Id, col, moves, l);
      SafeAddMoves(p, &Sub, &Id, col, moves, l);
      break;
    case QUEEN:
      SafeAddMoves(p, &Add, &Add, col, moves, l);
      SafeAddMoves(p, &Add, &Sub, col, moves, l);
      SafeAddMoves(p, &Sub, &Add, col, moves, l);
      SafeAddMoves(p, &Sub, &Sub, col, moves, l);
      SafeAddMoves(p, &Id,  &Add, col, moves, l);
      SafeAddMoves(p, &Id,  &Sub, col, moves, l);
      SafeAddMoves(p, &Add, &Id,  col, moves, l);
      SafeAddMoves(p, &Sub, &Id,  col, moves, l);
      break;
    case KING:
      //TODO: castling case -- see wiki page for condititions
      if (!piece->HasMoved()) {}

      SafeAddMove(p, Coord(x+1, y+1), col, moves, l);
      SafeAddMove(p, Coord(x+1, y-1), col, moves, l);
      SafeAddMove(p, Coord(x-1, y+1), col, moves, l);
      SafeAddMove(p, Coord(x-1, y-1), col, moves, l);
      SafeAddMove(p, Coord(x,   y+1), col, moves, l);
      SafeAddMove(p, Coord(x,   y-1), col, moves, l);
      SafeAddMove(p, Coord(x+1, y),   col, moves, l);
      SafeAddMove(p, Coord(x-1, y),   col, moves, l);
      break;
    default: return *moves;
  }

  return *moves;
}

// p = start point, m = end point
bool Board::SafeAddMove(Coord p, Coord m, PieceColour ownColour, vector<Coord>* moves, int l)
{
  if (m.OutOfRange()) return false;
  
  if (pieces[m.x][m.y]->GetType() == EMPTY)
  {
    if (!WillMoveCauseCheck(p, m, l)) moves->push_back(m);
    return true;
  }

  // If we hit one of our own pieces stop highlighting.
  if (pieces[m.x][m.y]->GetColour() == ownColour)
  {
    return false;
  }
  // If we hit one of opponent's pieces, highlight that piece then stop highlighting.
  else
  {
    if (!WillMoveCauseCheck(p, m, l)) moves->push_back(m);
    return false;
  }
}

// p = start point
void Board::SafeAddMoves(Coord p, int (*fx)(int, int), int (*fy)(int, int), PieceColour ownColour, vector<Coord>* moves, int l)
{
  for (int n=1; n < 8; n++)
  {
    Coord move = Coord(fx(p.x, n), fy(p.y, n));
    if (!SafeAddMove(p, move, ownColour, moves, l)) break;
  }
}

bool Board::SafeAddMovePawn(Coord p, Coord m, vector<Coord>* moves, int l)
{
  if (m.OutOfRange()) return false;

  // Pawns can only move forwards if the square infront is empty.
  if (pieces[m.x][m.y]->GetType() == EMPTY)
  {
    if (!WillMoveCauseCheck(p, m, l)) moves->push_back(m);
    return true;
  }
}

bool Board::SafeAddMovePawnTake(Coord p, Coord m, PieceColour col, vector<Coord>* moves, int l)
{
  if (m.OutOfRange()) return false;

  // Pawns can only take if diagonal square is occupied by enemy piece.
  if (pieces[m.x][m.y]->GetType() != EMPTY && pieces[m.x][m.y]->GetColour() != col)
  {
    if (!WillMoveCauseCheck(p, m, l)) moves->push_back(m);
    return true;
  }
}

void Board::UnhighlightPieces()
{
  int i, j;
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j]->SetHighlighted(false);
    }
  }
}

/* Board analysis functions */

// IN PROGRESS...

// Returns the board state that would arise if the piece in location (xs, ys) was moved to (xs, ye).
bool Board::WillMoveCauseCheck(Coord s, Coord e, int l)
{
  // Don't care if moves more than one move ahead cause check.
  if (l > 0) return false;
  bool isCheck;

  // 1. Save current board state.
  Piece* oldEndPiece = pieces[e.x][e.y];

  // 2. Move piece to suggested location on board.
  pieces[e.x][e.y] = pieces[s.x][s.y];
  pieces[s.x][s.y] = new Piece(EMPTY);

  // 3. If white turn and move causes white check then yes.
  // OR If black turn and move causes black check then yes.
  isCheck = ((whiteToMove && IsInCheck(WHITE, l)) || (!whiteToMove && IsInCheck(BLACK, l)));

  // 4. Reset board back to how it was.
  pieces[s.x][s.y] = pieces[e.x][e.y];
  pieces[e.x][e.y] = oldEndPiece;

  return isCheck;
}

bool Board::IsInCheck(PieceColour colourToCheck, int l)
{
  int i, j;
  Coord kingCoord = Coord(-1, -1);
  vector<Coord> moves;

  // 1. Find location of king we are checking.
  // 2. Check if moves of other pieces overlap kings coordinates.
  for (i = 0; i < 8; i++) 
  {
    for (j = 0; j < 8; j++) 
    {
      Piece* p = pieces[i][j];
      if (p->GetType() == KING && p->GetColour() == colourToCheck)
      {
        kingCoord = Coord(i, j);
      }
      else if (p->GetColour() == !colourToCheck)
      {
        vector<Coord> newMoves = GetPossibleMoves(Coord(i, j), l+1);
        moves.insert(moves.end(), newMoves.begin(), newMoves.end());
      }
    }
  }

  for (vector<Coord>::iterator it = moves.begin(); it != moves.end(); ++it)
  {
    Coord m = *it;
    if (m.Equals(kingCoord)) return true;
  }

  return false;
}

// Piece* Board::CreateBoardClone()
// {
//   Piece piecesClone[8][8] = new Piece[8][8];
//   int i, j;
//   for (i = 0; i < 8; i++) 
//   {
//     for (j = 0; j < 8; j++) 
//     {
//       piecesClone[i][j] = *pieces[i][j];
//     }
//   }

//   Piece* p = piecesClone;
//   return p;

// }

// BoardState Board::AnalyseBoardState()
// {
//   BoardState bs;
//   if (IsInCheck(BLACK))
//   {
//     return CHECK_BLACK;
//   }

//   if (IsInCheck(WHITE))
//   {
//     return CHECK_WHITE;
//   }
// }