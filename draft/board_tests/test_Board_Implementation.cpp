#include "test_Board_Implementation.h"
using namespace std;

namespace CFBoardTester {

void test_pieceIdToChar(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = { // check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_pieceIdToChar ";
    std::cout << "[";
    for (auto test : tests) {
        //Implement
    }
}

void test_pieceCharToId(){
    char test[12] = {'P', 'p', 'N', 'n', 'B', 'b', 'R', 'r', 'Q', 'q', 'K', 'k'};
    char out[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::cout << "test_pieceCarToId ";
    std::cout << "[";
    bool TF = true
    for (int i=0; i<12; i++) {
        if(test[i] != out[i]) {
            cout << "Failure";
                .TF = false;
        }
    }
    if (TF == true){
        cout << "Success";        
    }
}

void test_getColorBitBoard(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = { // check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getColorBitBoard ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getPieceColorBitBoard(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = { // check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getPieceColorBitBoard ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getPieceBoardFromIndex(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_etPieceBoardFromIndex ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getCurrentPlayer(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getCurrentPlayer ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getPieceFromCoords(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getPieceFromCoords ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getBit(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getBit ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getMaterialCount(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getMaterialCount ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_addPiece(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_addPiece ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_removePiece(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_removePiece ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_movePiece(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_movePiece ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_forceUndo(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_forceUndo ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getCardinals(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getCardinals ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getDiagonals(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getDiagonals ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getKnightPattern(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getKnightPattern ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getKingPattern(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getKingPattern ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getPawnPattern(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {// check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getPawnPattern ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}
void test_getLegalMoves(){
    std::vector<std::tuple<bool, bool, CFBoard>> tests = { // check test cases
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "test_getLegalMoves ";
    std::cout << "[";
    for (auto test : tests) {
        //implement
    }
}

void testNaiveCheckCheck() {
    std::vector<std::tuple<bool, bool, CFBoard>> tests = {
        std::make_tuple(false, false, CFBoard()),
        std::make_tuple(true, true,
                        CFBoard("rnbqkbnr/ppp1pppp/3p4/8/Q7/2P5/PP1PPPPP/"
                                "RNBQKBNR w KQkq - 0 1"))};
    std::cout << "testNaiveCheckCheck ";
    std::cout << "[";
    for (auto test : tests) {
        bool isCheck = std::get<0>(test);
        if (isCheck == std::get<2>(test).naiveCheckCheck(std::get<1>(test))) {
            std::cout << "P";
        } else {
            std::cout << "-";
        }
    }
    std::cout << "]" << std::endl;
}

void test_ToFEN() {
    std::vector<std::pair<std::string, CFBoard>> tests = {std::make_pair(
        std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"),
        CFBoard())};
    std::cout << "testToFEN ";
    std::cout << "[";
    for (auto test : tests) {
        std::string fen = test.first;
        std::string ret = test.second.toFEN();
        if (ret == fen) {
            std::cout << "P";
        } else {
            std::cout << "-";
        }
    }
    std::cout << "]" << std::endl;
}

void test_FromFEN() {
    std::vector<std::pair<std::string, CFBoard>> tests = {std::make_pair(
        std::string("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"),
        CFBoard())};
    std::cout << "testFromFEN ";
    std::cout << "[";
    for (auto test : tests) {
        std::string fen = test.first;
        CFBoard board = test.second;
        if (board == CFBoard(fen)) {
            std::cout << "P";
        } else {
            std::cout << "-";
        }
    }
    std::cout << "]" << std::endl;
}
} // namespace CFBoardTester
  
