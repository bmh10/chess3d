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

  // If move puts current player in check then disallow - TODO: filter out these moves in selected squares.
  // if (IsInCheck(whiteToMove ? WHITE : BLACK))
  // {
  //   pieces[i][j] = new Piece(EMPTY);
  //   pieces[selCoord[0]][selCoord[1]] = selectedPiece;
  //   return;
  // }

  // Switch turns
  selectedPiece->SetHasMoved();
  selectedPiece = NULL;
  whiteToMove = !whiteToMove;
  camera->RotateToWhite(whiteToMove);

  // After move calculate board state i.e. see if anyone in in check, stalemate or checkmate.
  //boardState = IsInCheck(whiteToMove ? WHITE : BLACK) ? CHECK : STANDARD;
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
  vector<Coord> moves = GetPossibleMoves(Coord(selCoord[0], selCoord[1]));

  for(vector<Coord>::iterator it = moves.begin(); it != moves.end(); ++it)
  {
    pieces[(*it).x][(*it).y]->SetHighlighted(true);
  }
}

// Gets the possible moves for the piece at (i, j) as a vector of coords.
vector<Coord> Board::GetPossibleMoves(Coord p)
{
  vector<Coord>* moves = new vector<Coord>();
  if (p.x < 0 || p.x > 7 || p.y < 0 || p.y > 7) return *moves;

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
      

      if (SafeAddMovePawn(Coord(x, y+i), moves)
        && ((y == 1 && col == WHITE) || (y == 6 && col == BLACK)))
      {
        // Pawns can move 2 squares only from start position
        SafeAddMovePawn(Coord(x, y+2*i), moves);
      }

      // Pawns take diagonally
      SafeAddMovePawnTake(Coord(x+1, y+i), col, moves);
      SafeAddMovePawnTake(Coord(x-1, y+i), col, moves);

      //TODO: en passent case
      break;
    case KNIGHT:
      SafeAddMove(Coord(x+1, y+2), col, moves);
      SafeAddMove(Coord(x+1, y-2), col, moves);
      SafeAddMove(Coord(x-1, y+2), col, moves);
      SafeAddMove(Coord(x-1, y-2), col, moves);
      SafeAddMove(Coord(x+2, y+1), col, moves);
      SafeAddMove(Coord(x+2, y-1), col, moves);
      SafeAddMove(Coord(x-2, y+1), col, moves);
      SafeAddMove(Coord(x-2, y-1), col, moves);
      break;
    case BISHOP:
      SafeAddMoves(Coord(x, y), &Add, &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Add, &Sub, col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Sub, col, moves);
      break;
    case CASTLE:
      SafeAddMoves(Coord(x, y), &Id, &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Id, &Sub, col, moves);
      SafeAddMoves(Coord(x, y), &Add, &Id, col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Id, col, moves);
      break;
    case QUEEN:
      SafeAddMoves(Coord(x, y), &Add, &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Add, &Sub, col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Sub, col, moves);
      SafeAddMoves(Coord(x, y), &Id,  &Add, col, moves);
      SafeAddMoves(Coord(x, y), &Id,  &Sub, col, moves);
      SafeAddMoves(Coord(x, y), &Add, &Id,  col, moves);
      SafeAddMoves(Coord(x, y), &Sub, &Id,  col, moves);
      break;
    case KING:
      //TODO: castling case -- see wiki page for condititions
      if (!selectedPiece->HasMoved()) {}

      SafeAddMove(Coord(x+1, y+1), col, moves);
      SafeAddMove(Coord(x+1, y-1), col, moves);
      SafeAddMove(Coord(x-1, y+1), col, moves);
      SafeAddMove(Coord(x-1, y-1), col, moves);
      SafeAddMove(Coord(x,   y+1), col, moves);
      SafeAddMove(Coord(x,   y-1), col, moves);
      SafeAddMove(Coord(x+1, y),   col, moves);
      SafeAddMove(Coord(x-1, y),   col, moves);
      break;
    default: return *moves;
  }

  return *moves;
}

bool Board::SafeAddMove(Coord m, PieceColour ownColour, vector<Coord>* moves)
{
  if (m.x < 0 || m.x > 7 || m.y < 0 || m.y > 7) return false;
  
  if (pieces[m.x][m.y]->GetType() == EMPTY)
  {
    moves->push_back(m);
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
    moves->push_back(m);
    return false;
  }
}

void Board::SafeAddMoves(Coord start, int (*fx)(int, int), int (*fy)(int, int), PieceColour ownColour, vector<Coord>* moves)
{
  for (int n=1; n < 8; n++)
  {
    Coord move = Coord(fx(start.x, n), fy(start.y, n));
    if (!SafeAddMove(move, ownColour, moves)) break;
  }
}

bool Board::SafeAddMovePawn(Coord m, vector<Coord>* moves)
{
  if (m.x < 0 || m.x > 7 || m.y < 0 || m.y > 7) return false;

  if (pieces[m.x][m.y]->GetType() == EMPTY)
  {
    moves->push_back(m);
    return true;
  }
}

bool Board::SafeAddMovePawnTake(Coord m, PieceColour col, vector<Coord>* moves)
{
  if (m.x < 0 || m.x > 7 || m.y < 0 || m.y > 7) return false;

  if (pieces[m.x][m.y]->GetType() != EMPTY && pieces[m.x][m.y]->GetColour() != col)
  {
    moves->push_back(m);
    return true;
  }
}

// void Board::DisplayPossibleMoves()
// {
//   if (selectedPiece == NULL) return;

//   int x = selCoord[0];
//   int y = selCoord[1];
//   PieceColour col = selectedPiece->GetColour();
//   int i = (col == WHITE) ? 1 : -1;
//   switch (selectedPiece->GetType())
//   {
//     case EMPTY: return;
//     case PAWN:
//       if (SafeHighlightPiecePawn(x, y+i)
//          && ((y == 1 && col == WHITE) || (y == 6 && col == BLACK)))
//       {
//         // Pawns can move 2 squares only from start position
//         SafeHighlightPiecePawn(x, y+2*i);
//       }

//       // Pawns take diagonally
//       SafeHighlightPiecePawnTake(x+1, y+i, col);
//       SafeHighlightPiecePawnTake(x-1, y+i, col);

//       //TODO: en passent case
//       break;
//     case KNIGHT:
//       SafeHighlightPiece(x+1, y+2);
//       SafeHighlightPiece(x+1, y-2);
//       SafeHighlightPiece(x-1, y+2);
//       SafeHighlightPiece(x-1, y-2);
//       break;
//     case BISHOP:
//       SafeHighlightPieces(x, y, &Add, &Add);
//       SafeHighlightPieces(x, y, &Add, &Sub);
//       SafeHighlightPieces(x, y, &Sub, &Add);
//       SafeHighlightPieces(x, y, &Sub, &Sub);
//       break;
//     case CASTLE:
//       SafeHighlightPieces(x, y, &Id, &Add);
// 	    SafeHighlightPieces(x, y, &Id, &Sub);
//       SafeHighlightPieces(x, y, &Add, &Id);
//       SafeHighlightPieces(x, y, &Sub, &Id);
//       break;
//     case QUEEN:
//       SafeHighlightPieces(x, y, &Add, &Add);
//   	  SafeHighlightPieces(x, y, &Add, &Sub);
//   	  SafeHighlightPieces(x, y, &Sub, &Add);
//   	  SafeHighlightPieces(x, y, &Sub, &Sub);
//   	  SafeHighlightPieces(x, y, &Id, &Add);
//   	  SafeHighlightPieces(x, y, &Id, &Sub);
//   	  SafeHighlightPieces(x, y, &Add, &Id);
//   	  SafeHighlightPieces(x, y, &Sub, &Id);
//       break;
//     case KING:
//       //TODO: castling case -- see wiki page for condititions
//       if (!selectedPiece->HasMoved())
//       {
//         //SafeHighlightPiece(x+2, y);
//       }

//       SafeHighlightPiece(x+1, y+1);
//       SafeHighlightPiece(x+1, y-1);
//       SafeHighlightPiece(x-1, y+1);
//       SafeHighlightPiece(x-1, y-1);
//       SafeHighlightPiece(x, y+1);
//       SafeHighlightPiece(x, y-1);
//       SafeHighlightPiece(x+1, y);
//       SafeHighlightPiece(x-1, y);
//       break;
//     default: return;
//   }
// }

// /*
//  * Highlights a piece with given coordinates
//  * if coordinates are within confines of the board.
//  */
// bool Board::SafeHighlightPiece(int i, int j)
// {
//   if (i >= 0 && i < 8 && j >=0 && j < 8)
//   {
//     if (pieces[i][j]->GetType() != EMPTY)
//     {
//       // If we hit one of our own pieces stop highlighting.
//       if (pieces[i][j]->GetColour() == selectedPiece->GetColour())
//       {
//         return false;
//       }
//       // If we hit one of opponent's pieces highlight that piece then stop highlighting.
//       else
//       {
//         pieces[i][j]->SetHighlighted(true);
//         return false;
//       }
//     }
//     pieces[i][j]->SetHighlighted(true);
//     return true;
//   }
//   return false;
// }

// void Board::SafeHighlightPieces(int i, int j, int (*fx)(int, int), int (*fy)(int, int))
// {
//   int n;
//   for (n=1; n < 8; n++)
//   {
// 	  if (!SafeHighlightPiece(fx(i, n), fy(j, n)))
//       break;
//   }
// }

// bool Board::SafeHighlightPiecePawn(int i, int j)
// {
//   if (i >= 0 && i < 8 && j >=0 && j < 8)
//   {
//     if (pieces[i][j]->GetType() == EMPTY)
//     {
//       pieces[i][j]->SetHighlighted(true);
//       return true;
//     }
//   }
//   return false;
// }

// bool Board::SafeHighlightPiecePawnTake(int i, int j, PieceColour col)
// {
//   if (i >= 0 && i < 8 && j >=0 && j < 8)
//   {
//     if (pieces[i][j]->GetType() != EMPTY
//         && pieces[i][j]->GetColour() != col)
//       {
//         pieces[i][j]->SetHighlighted(true);
//         return true;
//       }
//   }
//   return false;
// }

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

void Board::Toggle2dMode()
{
  show2dBoard = !show2dBoard;
}

/* Board analysis functions */

// IN PROGRESS...

// // Returns the board state that would arise if the piece in location (xs, ys) was moved to (xs, ye).
// BoardState AnalyseMove(int xs, int ys, int xe, int ye)
// {
//   pieces[xe][ye] = pieces[xs][xs];
//   pieces[xs][ys] = new Piece(EMPTY);

//   // If move puts current player in check then disallow - TODO: filter out these moves in selected squares.
//   if (IsInCheck(whiteToMove ? WHITE : BLACK))
//   {
//     pieces[i][j] = new Piece(EMPTY);
//     pieces[selCoord[0]][selCoord[1]] = selectedPiece;
//     return;
//   }

//   // Switch turns
//   selectedPiece->SetHasMoved();
//   selectedPiece = NULL;
//   whiteToMove = !whiteToMove;
//   camera->RotateToWhite(whiteToMove);

//   // After move calculate board state i.e. see if anyone in in check, stalemate or checkmate.
//   boardState = IsInCheck(whiteToMove ? WHITE : BLACK) ? CHECK : STANDARD;
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

// bool Board::IsInCheck(PieceColour colourToCheck)
// {


// }










  // TODO: do this a better/more efficient way which doesn't involve
  // directly highlighting all moves -> just get moves as a list of coords.
  // int i, j;
  // Piece* king;
  // Piece* selectedPieceTemp = selectedPiece;
  // int selCoordTemp[] = {selCoord[0], selCoord[1]};

  // // 1. Find location of king we are checking.
  // // 2. Check if moves of other pieces intersect.
  // for (i = 0; i < 8; i++) 
  // {
  //   for (j = 0; j < 8; j++) 
  //   {
  //     Piece* p = pieces[i][j];
  //     if (p->GetType() == KING && p->GetColour() == colourOfKingToCheck)
  //     {
  //       king = p;
  //     }
  //     else if (p->GetColour() == !colourOfKingToCheck)
  //     {
  //       selectedPiece = p;
  //       selCoord[0] = i;
  //       selCoord[1] = j;
  //       DisplayPossibleMoves();
  //     }
  //   }
  // }

  // // TODO: doesnt take into account that pawns can't take forwards!!
  // bool inCheck = king->GetState() == HIGHLIGHTED;
  // if (inCheck) cout << colourOfKingToCheck << " KING IN CHECK!!" << endl;

  // // Reset selected piece to original.
  // selectedPiece = selectedPieceTemp;
  // selCoord[0] = selCoordTemp[0];
  // selCoord[1] = selCoordTemp[1];
  // UnhighlightPieces();

  // return inCheck;
// }