#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

/*
 * make chess board
 * made pieces and sprites
 * drag and drop pieces
 * created order of moves white, bvl
 *
 * TODO 
 * moves, valid moves of pieces
 * checks checkmates
 * 
 * engine 
 *
 * */

using namespace std;

struct Move{
	int rowChange;
	int columnChange;
};

class Piece{
	private:
		string type;
		bool isWhite;
		bool hasMovedOnce;
		sf::Sprite* sprite;
	public:
		Move* possibleMoves[100];

		string getType(){
			return type;
		}
		bool getColour(){
			return isWhite;
		}
		sf::Sprite* getSprite(){
			return sprite;
		}
		void setSprite(sf::Sprite* S){
			sprite = S;	
		}
		void addMove(int rowChange, int colChange){
			Move* M = new Move;
			M->rowChange = rowChange;	
			M->columnChange = colChange;	
			possibleMoves[findFreeIndex()] = M;
		}
		int findFreeIndex(){
			for(int i=0; i<100; i++){
				if(possibleMoves[i] == nullptr){
					return i; 
				}
			}
			return -1;
		}
		void freeMoves(){
			int count = 0;
			for(int i=0; i<100; i++){
				if(possibleMoves[i] != nullptr){
					delete possibleMoves[i];
					count++;
				}
			}
			cout << "Deleted " << count << " moves" << endl;
		}
		void setMovedOnce(){
			hasMovedOnce = true;
		}
		void setMoveOnceBack(){
			hasMovedOnce = false;
		}
		bool getMovedOnceState(){
			return hasMovedOnce;
		}

		Piece(string T, bool C){
			type = T;
			isWhite = C;
			hasMovedOnce = false;
			sprite = nullptr;
			for(int i=0; i<100; i++){
				possibleMoves[i] = nullptr;	
			}
		}
};

class Square{
	private:
		bool PieceInSquare;
		Piece* pPiece;
	public:
		bool isSquareOccupied(){
			return PieceInSquare;
		}

		void setPiece(Piece* P){
			pPiece = P;
			PieceInSquare = true;
		}

		Piece* getPieceInSquare(){
			return pPiece;
		}
		void removePiece(){
			pPiece = nullptr;
			PieceInSquare=false;
		}
		Square(){
			PieceInSquare = false;
			pPiece = nullptr;
		}
};

class Game{

	private:
		string whitePieces[8] = {"rook", "knight","bishop","queen","king","bishop","knight","rook"};
		string blackPieces[8] = {"rook", "knight","bishop","queen","king","bishop","knight","rook"};
		int CurrentPlayer;
	public:
		Square Board[8][8];
		
		void makeBoard(){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					Square S;
					Board[i][j] = S;
				}
			}
			createPieces();
		}
		
		void createPieces(){
			// White Pieces, pawns
			for(int i=0; i<8; i++){
				Piece* P = new Piece("pawn", true);
				Board[i][6].setPiece(P);

				// white pawn move create
				P->addMove(0, -1);
				P->addMove(0, -2);
				P->addMove(1, -1);
				P->addMove(-1, -1);

				Piece* D = new Piece(whitePieces[i], true);
				Board[i][7].setPiece(D);
				
				// rook moves create
				if(whitePieces[i] == "rook"){
					for(int i=-7; i<8; i++){
						D->addMove(i, 0);
						D->addMove(0, i);
					}
				}
				// bishop moves
				if(whitePieces[i] == "bishop"){
					for(int i=-7; i<8; i++){
						D->addMove(i, i);
						D->addMove(i, -i);
						D->addMove(-i, i);
					}
				}

				// knight moves
				if(whitePieces[i] == "knight"){
					D->addMove(2, 1);
					D->addMove(2, -1);
					D->addMove(1, 2);
					D->addMove(1, -2);
					D->addMove(-1, -2);
					D->addMove(-2, 1);
					D->addMove(-2, -1);
					D->addMove(-1, 2);
				}

				// Queen moves
				if(whitePieces[i] == "queen"){
					for(int i=-7; i<8; i++){
						D->addMove(0, i);
						D->addMove(i, 0);
						D->addMove(i, i);
						D->addMove(i, -i);
						D->addMove(-i, i);
					}
				}

				//King moves
				if(whitePieces[i] == "king"){
					D->addMove(1, 0);
					D->addMove(-1, 0);
					D->addMove(0, 1);
					D->addMove(0, -1);
					D->addMove(1, 1);
					D->addMove(1, -1);
					D->addMove(-1, 1);
					D->addMove(-1, -1);
				}

				Piece* Q = new Piece(blackPieces[i], false);
				Board[i][0].setPiece(Q);

				if(blackPieces[i] == "rook"){
					for(int i=-7; i<8; i++){
						Q->addMove(i, 0);
						Q->addMove(0, i);
					}
				}

				// bishop moves
				if(blackPieces[i] == "bishop"){
					for(int i=-7; i<8; i++){
						Q->addMove(i, i);
						Q->addMove(i, -i);
						Q->addMove(-i, i);
					}
				}

				// knight moves
				if(blackPieces[i] == "knight"){
					Q->addMove(2, 1);
					Q->addMove(2, -1);
					Q->addMove(1, 2);
					Q->addMove(1, -2);
					Q->addMove(-1, -2);
					Q->addMove(-2, 1);
					Q->addMove(-2, -1);
					Q->addMove(-1, 2);
				}

				// Queen moves
				if(blackPieces[i] == "queen"){
					for(int i=-7; i<8; i++){
						Q->addMove(0, i);
						Q->addMove(i, 0);
						Q->addMove(i, i);
						Q->addMove(i, -i);
						Q->addMove(-i, i);
					}
				}

				//King moves
				if(blackPieces[i] == "king"){
					Q->addMove(1, 0);
					Q->addMove(-1, 0);
					Q->addMove(0, 1);
					Q->addMove(0, -1);
					Q->addMove(1, 1);
					Q->addMove(1, -1);
					Q->addMove(-1, 1);
					Q->addMove(-1, -1);
				}
				Piece* R = new Piece("pawn", false);
				Board[i][1].setPiece(R);

				// black pawn move create
				R->addMove(0, 1);
				R->addMove(0, 2);
				R->addMove(1, 1);
				R->addMove(-1, 1);
			}
		}

		// Function that take mouse coordinates and turns it into square
		Square* turnMouseCoordsToSquare(int x, int y){
			if(x/116 > 7 || x/116 < 0 || y/116 > 7 || y/116 < 0){
				return nullptr;
			}
			return &Board[x/116][y/116];
		}

		void turnMouseCoordsToBoard(int x, int y){
			cout << x/116 << ", " << y/116 << endl;
		}

		int getCurrentPlayer(){
			return CurrentPlayer;
		}

		void incrimentCurrentPlayer(){
			CurrentPlayer++;
			CurrentPlayer %= 2;
		}

		bool isValidMove(int startIndex[2], int finishIndex[2], Piece* P){
			for(int i=0; i<2; i++){
				if(startIndex[i] > 7 || startIndex[i] < 0 || finishIndex[i] > 7 || finishIndex[i] < 0){
					cout << "Out of range" << endl;
					return false;
				}
			}
			for(int i=0; i<100; i++){
				Move* M = P->possibleMoves[i];
				if(M == nullptr){
					continue;
				}
				if((M->rowChange + startIndex[0] == finishIndex[0]) && M->columnChange + startIndex[1] == finishIndex[1]){
					
					// Pawn Rules 
					if(P->getType() == "pawn"){
						// Pawn double advance rule
						if(M->columnChange == -2 || M->columnChange == 2){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() != nullptr){
								return false;
							}
							if(Board[finishIndex[0]][finishIndex[1] - M->columnChange/2].getPieceInSquare() != nullptr){
								return false;	
							}	
							if(!P->getMovedOnceState()){
								return true;
							}
							continue;
						}

						// Pawn capture rule
						if(M->rowChange == 1 || M->rowChange == -1){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() == nullptr){
								return false;
							}
							else{
								return true;	
							}
						}

						if(M->columnChange == 1 || M->columnChange == -1){
							if(Board[finishIndex[0]][finishIndex[1]].getPieceInSquare() != nullptr){
								return false;
							}
							return true;
						}
					}

					if(P->getType() == "knight"){
						return true;
					}

					int rowC = M->rowChange;
					int colC = M->columnChange;
					int rowMultiplier = 1;
					int colMultiplier = 1;

					if(rowC < 0){
						rowC *= -1;
						rowMultiplier = -1;
					}
					if(colC < 0){
						colC *= -1;
						colMultiplier = -1;
					}

					int CurrentIndex[2] = {startIndex[0], startIndex[1]};
					bool validRouteFound = true;

					for(int i=0; i<rowC-1; i++){
						CurrentIndex[0] += 1 * rowMultiplier;
						if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
							validRouteFound = false;	
						}
					}

					for(int i=0; i<colC-1; i++){
						CurrentIndex[1] += 1 * colMultiplier;
						if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
							validRouteFound = false;	
						}
					}
					
					if(P->getType() == "bishop" || P->getType() == "queen" && (rowC == colC)){
						validRouteFound = true;
						CurrentIndex[0] = startIndex[0];
						CurrentIndex[1] = startIndex[1];
						for(int i=0; i<rowC-1; i++){
							CurrentIndex[0] += 1 * rowMultiplier;
							CurrentIndex[1] += 1 * colMultiplier;
							if(Board[CurrentIndex[0]][CurrentIndex[1]].getPieceInSquare() != nullptr){
								validRouteFound = false;	
							}
						}
					}
					
					if(validRouteFound){
						return true;
					}
				}
			}
			return false;
		}

		void drawBoard(sf::RenderWindow* window, sf::Texture* TBoard, sf::Texture* TPieces){
			float  sf_S = 1.55f;
			float  sf_P = 0.75f;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					sf::Sprite BoardSquare;
					BoardSquare.setTexture(*TBoard);
					BoardSquare.setTextureRect(sf::IntRect(648, 114 , 69, 69));
					BoardSquare.scale(sf::Vector2f(sf_S, sf_S));
					BoardSquare.setPosition(sf::Vector2f(75*i*sf_S, 75*j*sf_S));
					if((i+j) % 2 != 0){
						BoardSquare.setColor(sf::Color(255, 255, 255, 175));
					}
					window->draw(BoardSquare);
					drawPieces(window, TBoard, TPieces);
				}
			}
		}
		
		void drawValidMoves(sf::RenderWindow* window, sf::Texture* TCircle, Square* viewedSquare, int Index[2]){
			bool notMovedOnce = false;
			if(viewedSquare != nullptr){
				for(int i=0; i<8; i++){
					for(int j=0; j<8; j++){
						sf::Sprite S;
						S.setTexture(*TCircle);
						S.setScale(sf::Vector2f(0.03f, 0.03f));
						S.setColor(sf::Color(0, 0, 0, 128));
						int D[2] = {i, j};
						if(isValidMove(Index, D, viewedSquare->getPieceInSquare())){
							if(Board[i][j].getPieceInSquare() != nullptr){
								if(Board[i][j].getPieceInSquare()->getColour() == viewedSquare->getPieceInSquare()->getColour()){
									continue;
								}
							}

							if(notMovedOnce){
								viewedSquare->getPieceInSquare()->setMoveOnceBack();
							}

							S.setPosition(sf::Vector2f(117*i +30, 117*j + 40));
							window->draw(S);
						}
					}
				}
			}
		}

		void drawPieces(sf::RenderWindow* window, sf::Texture* TBoard, sf::Texture* TPieces){
			float  sf_S = 1.55f;
			float  sf_P = 0.75f;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					if(Board[i][j].isSquareOccupied()){
						int colour_sf = 1;
						int multiplier = 0;
						string type = Board[i][j].getPieceInSquare()->getType();
						if(Board[i][j].getPieceInSquare()->getColour()){
							colour_sf = 0;	
						}
						if(type == "king"){
							multiplier = 0;
						}
						if(type == "queen"){
							multiplier = 1;
						}
						if(type == "bishop"){
							multiplier = 2;
						}
						if(type == "knight"){
							multiplier = 3;
						}
						if(type == "rook"){
							multiplier = 4;
						}
						if(type == "pawn"){
							multiplier = 5;
						}
						if(Board[i][j].getPieceInSquare()->getSprite() == nullptr){
							sf::Sprite* Piece = new sf::Sprite;
							Board[i][j].getPieceInSquare()->setSprite(Piece);
							Piece->setTexture(*TPieces);
							Piece->setTextureRect(sf::IntRect(133*multiplier, 133*colour_sf, 133, 133));
							Piece->scale(sf::Vector2f(sf_P, sf_P));
							Piece->setPosition(sf::Vector2f(117*i + 45,117*j + 40));
							Piece->setOrigin(sf::Vector2f(165*sf_P/2, 133*sf_P/2));
							window->draw(*Piece);
						}
						else{
							window->draw(*Board[i][j].getPieceInSquare()->getSprite());
						}
					}
				}
			}
		}

		Game(){
			CurrentPlayer = 1;
		}

		~Game(){
			int count = 0;
			cout << "Deconstructor..." << endl;
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					if(Board[i][j].isSquareOccupied()){
						if(Board[i][j].getPieceInSquare() != nullptr){
							cout << "Removing " << Board[i][j].getPieceInSquare()->getType() << ", and its sprite" << endl;
							delete Board[i][j].getPieceInSquare();
							delete Board[i][j].getPieceInSquare()->getSprite();
							Board[i][j].getPieceInSquare()->freeMoves();
							count++;
						}
					}
				}
			}
			cout << "Deleted, " << count;
		}
};

int main()
{	
	Piece* PieceHeldDown = nullptr;
	Square* SquareStart = nullptr;
	Square* LastPiecePressed = nullptr;
	sf::SoundBuffer ChessPieceMove;
	sf::SoundBuffer ChessPieceCapture;
	int LastIndex[2] = {-1, -1};
	int Index[2] = {0, 0};

	sf::RenderWindow window(sf::VideoMode(800, 1080), "Chess");
	sf::Texture ChessPiecesT;
	sf::Texture BoardT;
	sf::Texture CircleT;
	sf::Sound pieceMoveSound;
	sf::Sound pieceCaptureSound;
	Game G;
	G.makeBoard();
	while (window.isOpen()){

		ChessPiecesT.loadFromFile("textures/chess_pieces.png");
		BoardT.loadFromFile("textures/more.png");
		CircleT.loadFromFile("textures/greycircle.png");
		ChessPieceMove.loadFromFile("audio/chessmove.wav");
		ChessPieceCapture.loadFromFile("audio/chesscapture.wav");
		pieceMoveSound.setBuffer(ChessPieceMove);
		pieceCaptureSound.setBuffer(ChessPieceCapture);
		ChessPiecesT.setSmooth(true);
		CircleT.setSmooth(true);

		sf::Event event;

		window.clear();

		G.drawBoard(&window, &BoardT, &ChessPiecesT);
		
		G.drawValidMoves(&window, &CircleT, LastPiecePressed, LastIndex);

		window.display();

		while(window.pollEvent(event)){
			
			if(event.type == sf::Event::Closed){
				window.close();
			}

			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				if(PieceHeldDown == nullptr){
					Square* S = G.turnMouseCoordsToSquare(x, y);
					if(S == nullptr){
						continue;
					}
					if(S->getPieceInSquare() == nullptr){
						continue;
					}
					//check colour
					if(!((G.getCurrentPlayer() == 1 && S->getPieceInSquare()->getColour() == true) || (G.getCurrentPlayer() == 0 && S->getPieceInSquare()->getColour() == false))){
						continue;
					}

					PieceHeldDown = S->getPieceInSquare();
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(x, y));
					SquareStart = S;
					LastPiecePressed = S;
					LastIndex[0] = x / 116;
					LastIndex[1] = y / 116;
					Index[0] = x;
					Index[1] = y;
				}
				else{
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(x, y));
				}
			}

			if(event.type == sf::Event::MouseButtonReleased){
				int x = sf::Mouse::getPosition(window).x;
				int y = sf::Mouse::getPosition(window).y;
				Square* S = G.turnMouseCoordsToSquare(x, y);	
				if(PieceHeldDown == nullptr){
					continue;
				}
				if(SquareStart == nullptr || SquareStart->getPieceInSquare() == nullptr){
					continue;
				}
				if(S == nullptr){
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;	
				}
				if(PieceHeldDown == S->getPieceInSquare()){
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;
				}

				int StartIndex[2] = {Index[0]/116, Index[1]/116};
				int FinishIndex[2] = {x/116, y/116};
				

				if(!G.isValidMove(StartIndex, FinishIndex, PieceHeldDown)){
					cout << "Invalid Move" << endl;
					PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
					PieceHeldDown = nullptr;
					SquareStart = nullptr;
					Index[0] = 0;
					Index[1] = 0;
					continue;
				}

				bool capture = false;
				if(S->getPieceInSquare() != nullptr){
					if(S->getPieceInSquare()->getColour() == PieceHeldDown->getColour()){
						PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(Index[0]/116) + 45, 117*(Index[1]/116) + 40));	
						PieceHeldDown = nullptr;
						SquareStart = nullptr;
						Index[0] = 0;
						Index[1] = 0;
						cout << "Same color" << endl;
						continue;
					}
					cout << "Deleting, " << S->getPieceInSquare()->getType() << endl;
					delete S->getPieceInSquare()->getSprite();
					delete S->getPieceInSquare();
					capture = true;
					S->removePiece();
				}

				PieceHeldDown->getSprite()->setPosition(sf::Vector2f(117*(x/116) + 45, 117*(y/116) + 40));	
				if(capture){
					pieceCaptureSound.play();
				}
				else{
					pieceMoveSound.play();	
				}
				if(PieceHeldDown->getType() == "pawn"){
					PieceHeldDown->setMovedOnce();
				}
				S->setPiece(PieceHeldDown);
				SquareStart->removePiece(); 
				PieceHeldDown = nullptr;
				SquareStart = nullptr;
				Index[0] = 0;
				Index[1] = 0;
				G.incrimentCurrentPlayer();
				LastPiecePressed = nullptr;
				LastIndex[0] = -1;
				LastIndex[1] = -1;
			}
		}
	}
	return 0;
}
