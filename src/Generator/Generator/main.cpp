//
//  main.cpp
//  Generator
//
//  Created by Ariel Flahaut on 23/11/2022.
//


#include "generator.hpp"
#include <iostream>
int main(int argc, const char * argv[]) {
    Chessboard chessboard;
    chessboard.single_generator(16);
    chessboard.visualize();
    std::cout<<std::endl;
    chessboard.completion();
    chessboard.visualize();
    return 0;
}
