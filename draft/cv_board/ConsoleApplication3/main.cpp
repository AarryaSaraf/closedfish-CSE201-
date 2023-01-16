#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "class_decl.h"
#include <Windows.h>
#include <wingdi.h>
#include <experimental/filesystem>
using namespace cv;
using namespace std;
vector <Square> rects;
Scalar whitelow = cv::Scalar(30, 24, 233);
Scalar whitehigh = cv::Scalar(36, 255, 255);
Scalar blacklow = cv::Scalar(40, 102, 143);
Scalar blackhigh = cv::Scalar(46, 255, 255);
//getPosition takes as an input a board object, player color and (x,y) coordinates on the board.
//It then converts the coordinates to a chess board coordinate system.
std::string getPosition(Board &board, int x, int y,Player col) {
    char white[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char black[] = { 'h','g','f','e','d','c','b','a' };
    std::string position;
    double squareSize = (board.right - board.left) / 8;
    if (col.color) {
        int index = (x - board.left) / squareSize;
        position = position + white[index];
        int index1 = (y - board.top) / squareSize;
        int num = 8 - index1;
        position = position + std::to_string(num);
    }
    else {
        int index = (x - board.left) / squareSize;
        position = position + black[index];
        int num  = (y - board.top) / squareSize;
        position = position + std::to_string(num);
    };

    return position;
}
//findRects takes as imput the image and color boundaries for the chessboard square colors, and then it proceeds
//to find the squares and return the overall board position on the screen.
void findRects(cv::Mat &img, cv::Scalar low, cv::Scalar high, cv::Scalar low1, cv::Scalar high1, COLOR color, COLOR color1,Board &board) {
    cv::Mat mask;
    cv::inRange(img, low, high, mask);
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    //cv::imshow("maska", mask);
    for (size_t i = 0; i < contours.size(); ++i) {
        cv::Rect boundRect = cv::boundingRect(contours[i]);
        if (abs(boundRect.width - boundRect.height) <= 2 && boundRect.width > 35) {//adds only squares
            rects.emplace_back(color, boundRect, boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
        
       }
    }
    
    cv::inRange(img, low1, high1, mask);
    cv::findContours(mask, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    //cv::imshow("maska", mask);
    for (size_t i = 0; i < contours.size(); ++i) {
        cv::Rect boundRect = cv::boundingRect(contours[i]);
        if (abs(boundRect.width - boundRect.height) <= 2 && boundRect.width > 35) {//adds only squares
            rects.emplace_back(color1, boundRect, boundRect.x + boundRect.width / 2, boundRect.y + boundRect.height / 2);
            

        }
    }

}
void drawRects(Mat &img) { //draws highlight squares on the image of the board
    for (size_t i = 0; i < rects.size(); ++i) {
        switch (rects[i].color) {
        case WHITE:
            cv::rectangle(img, rects[i].rec.tl(), rects[i].rec.br(), CV_RGB(255, 0, 0), 2);
            break;
        case BLACK:
            cv::rectangle(img, rects[i].rec.tl(), rects[i].rec.br(), CV_RGB(0, 0, 0), 2);
            break;
        };
    };
};

void addTiles(bool col,Board &board) { //adds tiles to a vector
    int size = board.width;
    char white[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    char black[] = { 'h','g','f','e','d','c','b','a' };
    int iter = size / 8;
    std::vector<Tile> Tiles;
    for (int i = 1; i <= 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (col) {
                Tile t(white[j], i);
                Tiles.push_back(t);
            }
            else {
                Tile t(black[j], i);
                Tiles.push_back(t);
            }
        }
    }
}

//board initialization only at the start of the game
void addPieces(Board &board){
    for (int i=1; i <= 8; i++) {
        board.Pieces.push_back(Piece('P', COLOR::WHITE, Tile(char(96 + i), 2)));
        board.Pieces.push_back(Piece('P', COLOR::BLACK, Tile(char(96 + i), 7)));
    };
    board.Pieces.push_back(Piece('K', COLOR::WHITE, Tile('e', 1)));
    board.Pieces.push_back(Piece('K', COLOR::BLACK, Tile('e', 8)));
    board.Pieces.push_back(Piece('Q', COLOR::WHITE, Tile('d', 1)));
    board.Pieces.push_back(Piece('Q', COLOR::BLACK, Tile('d', 8)));
    board.Pieces.push_back(Piece('R', COLOR::WHITE, Tile('a', 1)));
    board.Pieces.push_back(Piece('R', COLOR::WHITE, Tile('h', 1)));
    board.Pieces.push_back(Piece('R', COLOR::BLACK, Tile('a', 8)));
    board.Pieces.push_back(Piece('R', COLOR::BLACK, Tile('h', 8)));
    board.Pieces.push_back(Piece('N', COLOR::WHITE, Tile('b', 1)));
    board.Pieces.push_back(Piece('N', COLOR::WHITE, Tile('g', 1)));
    board.Pieces.push_back(Piece('N', COLOR::BLACK, Tile('b', 8)));
    board.Pieces.push_back(Piece('N', COLOR::BLACK, Tile('g', 8)));
    board.Pieces.push_back(Piece('B', COLOR::WHITE, Tile('c', 1)));
    board.Pieces.push_back(Piece('B', COLOR::WHITE, Tile('f', 1)));
    board.Pieces.push_back(Piece('B', COLOR::BLACK, Tile('c', 8)));
    board.Pieces.push_back(Piece('B', COLOR::BLACK, Tile('f', 8)));
}
/* 
void movePiece(string move, Board &board) {//executes the move, updates the board class
    //to do: Short and long castles, queen conversion
    //for some reason the main if isn't executed, check that
    char& piece = move[0];
    char& let = move[1];
    char& num = move[2];
    char& let1 = move[3];
    char& num1 = move[4];
    vector<Piece> piecescopy = board.Pieces;
    for (int i = 0; i < board.Pieces.size(); i++) {
        //remove taken piece
        if (let1 == board.Pieces[i].position.let && num1 == board.Pieces[i].position.cord) {
            piecescopy.erase(piecescopy.begin()+i-1);
        }
        // change coords of the moved piece
        cout << board.Pieces[i].position.let<<let <<num<<board.Pieces[i].position.cord<< endl;
        if (let==board.Pieces[i].position.let && num==board.Pieces[i].position.cord){
            cout << piecescopy[i].position.cord << endl;
            piecescopy[i].position.let = let1;
            piecescopy[i].position.cord = num1;
            cout << piecescopy[i].position.cord << endl;
        }
    }
    board.Pieces = piecescopy;
}
*/
bool use_mask;
Mat img; Mat templ; Mat mask; Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

Mat conv(Mat& img)
{
    Mat hsvImg;
    cvtColor(img, hsvImg, COLOR_BGR2HSV);
    return hsvImg;
}
void detectPieces(Board &board, Mat &img1, Mat &templ) {//works for black only, not for all pawns
    Mat img_orig;
    img1.copyTo(img_orig);
    //Mat grey_orig;
    //Mat grey_template;
    //cvtColor(templ,grey_template, COLOR_BGR2GRAY);
    //cvtColor(img1, grey_orig, COLOR_BGR2GRAY);
    //grey_template.copyTo(img_orig);
    Mat result;
    matchTemplate(img1, templ, result, TM_CCOEFF_NORMED);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = maxLoc;
    rectangle(img1, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
    //imshow(image_window, img_orig);
}

void matchingMethod(Board board,Mat& img, Mat& templ)
{
    /// Source image to display
    Mat img_display; Mat result;
    img.copyTo(img_display);//for later show off
    Mat imgh = conv(img);
    Mat templh = conv(templ);
    /// Create the result matrix - shows template responces
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create(result_cols, result_rows, CV_32FC1);

    /// Do the Matching and Normalize
    matchTemplate(imgh, templh, result, TM_CCORR_NORMED);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal;
    Point minLoc; Point maxLoc;
    Point matchLoc;


    //in my variant we create general initially positive mask 
    Mat general_mask = Mat::ones(result.rows, result.cols, CV_8UC1);
    for (int k = 0; k < 5; ++k)// look for N=5 objects
    {
        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, general_mask);
        //just to visually observe centering I stay this part of code:
        result.at<float>(minLoc) = 1.0;//
        result.at<float>(maxLoc) = 0.0;//

        matchLoc = maxLoc;
        //koeffitient to control neiboring:
//k_overlapping=1.- two neiboring selections can overlap half-body of     template
//k_overlapping=2.- no overlapping,only border touching possible
//k_overlapping>2.- distancing
//0.< k_overlapping <1.-  selections can overlap more then half 
        float k_overlapping = 1.7f;//little overlapping is good for my task

        //create template size for masking objects, which have been found,
        //to be excluded in the next loop run
        int template_w = ceil(k_overlapping * templ.cols);
        int template_h = ceil(k_overlapping * templ.rows);
        int x = matchLoc.x - template_w / 2;
        int y = matchLoc.y - template_h / 2;

        //shrink template-mask size to avoid boundary violation
        if (y < 0) y = 0;
        if (x < 0) x = 0;
        //will template come beyond the mask?:if yes-cut off margin; 
        if (template_w + x > general_mask.cols)
            template_w = general_mask.cols - x;
        if (template_h + y > general_mask.rows)
            template_h = general_mask.rows - y;

        //set the negative mask to prevent repeating
        Mat template_mask = Mat::zeros(template_h, template_w, CV_8UC1);
        template_mask.copyTo(general_mask(cv::Rect(x, y, template_w, template_h)));

        /// Show me what you got on main image and on result (
        rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
        //small correction here-size of "result" is smaller
        rectangle(result, Point(matchLoc.x - templ.cols / 2, matchLoc.y - templ.rows / 2), Point(matchLoc.x + templ.cols / 2, matchLoc.y + templ.rows / 2), Scalar::all(0), 2, 8, 0);
    }//for k= 0--5 
}
int  main() {  //when merging into the algo code change the name for the call
    //this func finds the board and initializes the main board class accordingly, storing all the data
    bool playerColor;
    Board board;
    Mat black_king = imread("C:\\Users\\dimit\\Desktop\\cps\\black_king.png");
    Mat black_queen = imread("C:\\Users\\dimit\\Desktop\\cps\\black_queen.png");
    Mat black_knight = imread("C:\\Users\\dimit\\Desktop\\cps\\black_knight.png");
    Mat black_knight1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_black_knight.png");
    Mat black_bishop = imread("C:\\Users\\dimit\\Desktop\\cps\\black_bishop.png");
    Mat black_bishop1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_black_bishop.png");
    Mat black_rook = imread("C:\\Users\\dimit\\Desktop\\cps\\black_rook.png");
    Mat black_rook1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_black_rook.png");
    Mat black_pawn = imread("C:\\Users\\dimit\\Desktop\\cps\\black_pawn.png");
    Mat black_pawn1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_black_pawn.png");
    Mat white_king = imread("C:\\Users\\dimit\\Desktop\\cps\\white_king.png");
    Mat white_queen = imread("C:\\Users\\dimit\\Desktop\\cps\\white_queen.png");
    Mat white_knight = imread("C:\\Users\\dimit\\Desktop\\cps\\white_knight.png");
    Mat white_knight1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_white_knight.png");
    Mat white_bishop = imread("C:\\Users\\dimit\\Desktop\\cps\\white_bishop.png");
    Mat white_bishop1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_white_bishop.png");
    Mat white_rook = imread("C:\\Users\\dimit\\Desktop\\cps\\white_rook.png");
    Mat white_rook1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_white_rook.png");
    Mat white_pawn = imread("C:\\Users\\dimit\\Desktop\\cps\\white_pawn.png");
    Mat white_pawn1 = imread("C:\\Users\\dimit\\Desktop\\cps\\b_white_pawn.png");
    //Takes the input image
    cv::Mat img = cv::imread("C:\\Users\\dimit\\Desktop\\testslika1.png");
    cv::Mat orig;
    //Switches to HSV
    img.copyTo(orig);
    matchingMethod(board, orig, black_king);
    matchingMethod(board, orig, black_queen);
    //matchingMethod(board, orig, black_pawn);
    //matchingMethod(board, orig, black_pawn1);
    //matchingMethod(board, orig, black_knight);
    //matchingMethod(board, orig, black_knight1);
    //matchingMethod(board, orig, black_bishop);
    //matchingMethod(board, orig, black_bishop1);
    //matchingMethod(board, orig, black_rook1);
    //matchingMethod(board, orig, black_rook);

    //matchingMethod(board, orig, white_king);
    //matchingMethod(board, orig, white_queen);
    //matchingMethod(board, orig, white_pawn);
    //matchingMethod(board, orig, white_pawn1);
    //matchingMethod(board, orig, white_knight);
    //matchingMethod(board, orig, white_knight1);
    //matchingMethod(board, orig, white_bishop);
    //matchingMethod(board, orig, white_bishop1);
    //matchingMethod(board, orig, white_rook1);
    //matchingMethod(board, orig, white_rook);
    //cv::imshow("test", img);
    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
    //White field detection
    findRects(img, blacklow, blackhigh, whitelow, whitehigh, COLOR::BLACK, COLOR::WHITE, board);
    //drawRects(orig);
    for (int i = 0; i < rects.size(); i++) {
        if (rects[i].rec.tl().x < board.left) {
            board.left = rects[i].rec.tl().x;
        }
        if (rects[i].rec.tl().y < board.top) {
            board.top = rects[i].rec.tl().y;
        }
        if (rects[i].rec.br().x > board.right) {
            board.right = rects[i].rec.br().x;
        }
        if (rects[i].rec.br().y > board.bottom) {
            board.bottom = rects[i].rec.br().y;
        }

    };
    ///storin the pieces
    board.width = board.right - board.left;
    board.height = board.bottom - board.top;
    Point p1(board.left + board.width / 16, board.top + 50);
    Point p3(board.left + board.width / 16, board.bottom + 20);
    Vec3b col1 = orig.at<Vec3b>(p1);
    Vec3b col2 = orig.at<Vec3b>(p3);
    cout << col1 << endl;
    cout << col2 << endl;
    //
    if (col2[0] > col1[0]) {
        playerColor = true;
    }
    else {
        playerColor = false;
    }
    //adding tiles and pieces
    addTiles(playerColor, board);
    addPieces(board);
    //
    Point p2(board.left + 50, board.top+board.height/16);
    Point p4(board.left + 20, board.bottom - board.width / 16);
    //rectangle(orig,p1,p2, Scalar(255, 0, 0) ,2,LINE_8); 
    //rectangle(orig, p3, p4, Scalar(255, 0, 0), 2, LINE_8);
    namedWindow("aa", WINDOW_NORMAL);
    imshow("aa", orig);
    cv::waitKey(0);
}