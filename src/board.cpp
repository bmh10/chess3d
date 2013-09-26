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
  selectedPiece = NULL;
  whiteToMove = true;
  
  // Initialize pieces
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

  pieces[3][0] = new Piece(KING, WHITE, modelManager);
  pieces[3][7] = new Piece(KING, BLACK, modelManager);
  pieces[4][0] = new Piece(QUEEN, WHITE, modelManager);
  pieces[4][7] = new Piece(QUEEN, BLACK, modelManager);
}

bool Board::IsWhiteToMove()
{
  return whiteToMove;
}

void Board::Draw()
{
  GLfloat red[] = {1.0, 0.0, 0.0, 1.0}; // Make static?
  GLfloat blue[] = {0.0, 0.0, 1.0};
  GLfloat *col = red;
  int i, j;

  // Draw board base
  glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(0.0, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 0.0, -0.01);
    glVertex3f(8*SQUARE_SIZE, 8*SQUARE_SIZE, -0.01);
    glVertex3f(0.0, 8*SQUARE_SIZE, -0.01);
  glEnd();

  // Draw pieces and squares (3D)
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      pieces[i][j]->Draw(i, j);
    }
  }

  // Draw pieces and squares (2D)
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
  if ((selCol == WHITE && whiteToMove)
   || (selCol == BLACK && !whiteToMove))
  {
    DisplayPossibleMoves();
  }
}

void Board::MoveSelectedPiece(int i, int j)
{
  pieces[i][j] = selectedPiece;
  pieces[selCoord[0]][selCoord[1]] = new Piece(EMPTY);
  selectedPiece = NULL;
  // Switch turns
  whiteToMove = !whiteToMove;
  camera->RotateToWhite(whiteToMove);
}

void Board::SelectSquareAt(int x, int y)
{
  GLfloat rgb[4];
  int i, j;
  EnableSelectionMode(true);
  glReadBuffer(GL_BACK);
  glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, rgb);
  //cout << "{" << rgb[0]<< ", " << rgb[1] << ", " << rgb[2] << ", " << rgb[3] << "}" << endl;
  
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      if (pieces[i][j]->CheckIfClicked(rgb))
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

void Board::DisplayPossibleMoves()
{
  if (selectedPiece == NULL) return;

  int x = selCoord[0];
  int y = selCoord[1];
  PieceColour col = selectedPiece->GetColour();
  int i = (col == WHITE) ? 1 : -1;
  switch (selectedPiece->GetType())
  {
    case EMPTY: return;
    case PAWN:
      if (SafeHighlightPiecePawn(x, y+i)
         && ((y == 1 && col == WHITE) || (y == 6 && col == BLACK)))
      {
        // Pawns can move 2 squares only from start position
        SafeHighlightPiecePawn(x, y+2*i);
      }

      // Pawns take diagonally
      SafeHighlightPiecePawnTake(x+1, y+i, col);
      SafeHighlightPiecePawnTake(x-1, y+i, col);

      //TODO: en passent case
      break;
    case KNIGHT:
      SafeHighlightPiece(x+1, y+2);
      SafeHighlightPiece(x+1, y-2);
      SafeHighlightPiece(x-1, y+2);
      SafeHighlightPiece(x-1, y-2);
      break;
    case BISHOP:
      SafeHighlightPieces(x, y, &Add, &Add);
      SafeHighlightPieces(x, y, &Add, &Sub);
      SafeHighlightPieces(x, y, &Sub, &Add);
      SafeHighlightPieces(x, y, &Sub, &Sub);
      break;
    case CASTLE:
      SafeHighlightPieces(x, y, &Id, &Add);
	    SafeHighlightPieces(x, y, &Id, &Sub);
      SafeHighlightPieces(x, y, &Add, &Id);
      SafeHighlightPieces(x, y, &Sub, &Id);
      break;
    case QUEEN:
      SafeHighlightPieces(x, y, &Add, &Add);
  	  SafeHighlightPieces(x, y, &Add, &Sub);
  	  SafeHighlightPieces(x, y, &Sub, &Add);
  	  SafeHighlightPieces(x, y, &Sub, &Sub);
  	  SafeHighlightPieces(x, y, &Id, &Add);
  	  SafeHighlightPieces(x, y, &Id, &Sub);
  	  SafeHighlightPieces(x, y, &Add, &Id);
  	  SafeHighlightPieces(x, y, &Sub, &Id);
      break;
    case KING:
      //TODO: castling case
      SafeHighlightPiece(x+1, y+1);
      SafeHighlightPiece(x+1, y-1);
      SafeHighlightPiece(x-1, y+1);
      SafeHighlightPiece(x-1, y-1);
      SafeHighlightPiece(x, y+1);
      SafeHighlightPiece(x, y-1);
      SafeHighlightPiece(x+1, y);
      SafeHighlightPiece(x-1, y);
      break;
    default: return;
  }
}

/*
 * Highlights a piece with given coordinates
 * if coordinates are within confines of the board.
 */
bool Board::SafeHighlightPiece(int i, int j)
{
  if (i >= 0 && i < 8 && j >=0 && j < 8)
  {
    if (pieces[i][j]->GetType() != EMPTY)
    {
      // If we hit one of our own pieces stop highlighting.
      if (pieces[i][j]->GetColour() == selectedPiece->GetColour())
      {
        return false;
      }
      // If we hit one of opponent's pieces highlight that piece then stop highlighting.
      else
      {
        pieces[i][j]->SetHighlighted(true);
        return false;
      }
    }
    pieces[i][j]->SetHighlighted(true);
    return true;
  }
  return false;
}

void Board::SafeHighlightPieces(int i, int j, int (*fx)(int, int), int (*fy)(int, int))
{
  int n;
  for (n=1; n < 8; n++)
  {
	  if (!SafeHighlightPiece(fx(i, n), fy(j, n)))
      break;
  }
}

bool Board::SafeHighlightPiecePawn(int i, int j)
{
  if (i >= 0 && i < 8 && j >=0 && j < 8)
  {
    if (pieces[i][j]->GetType() == EMPTY)
    {
      pieces[i][j]->SetHighlighted(true);
      return true;
    }
  }
  return false;
}

bool Board::SafeHighlightPiecePawnTake(int i, int j, PieceColour col)
{
  if (i >= 0 && i < 8 && j >=0 && j < 8)
  {
    if (pieces[i][j]->GetType() != EMPTY
        && pieces[i][j]->GetColour() != col)
      {
        pieces[i][j]->SetHighlighted(true);
        return true;
      }
  }
  return false;
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