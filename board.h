#pragma once
#include <iostream>
#include <string>
#include <vector>
#include"button.h"
#include<string>
using namespace std;
class Card {
public:
    std::string value;
    Button card;
    string path;
    int x, y;
    Card()
    {
        value = "";
        x = 0;
        y = 0;
    }
    Card(std::string v) : value(v) {}
    string return_path()
    {
        string temp = value;
        char last_char = temp.back();
        temp.pop_back();

         path = "cards/";
        if (last_char == 'H')
        {
            path += "hearts_";
            path += temp;
            path += ".png";
        }
        else if (last_char == 'D')
        {
            path += "diamonds_";
            path += temp;
            path += ".png";
        }
        else if (last_char == 'C')
        {
            path += "clubs_";
            path += temp;
            path += ".png";
        }
        else if (last_char == 'S')
        {
            path += "ace_";
            path += temp;
            path += ".png";
        }
        return path;
    }
};

class Board {
public:
    Button** grid;
    std::vector<std::vector<Card*>> board;
    int flag[10][10];
    int sequence;
    Board() {
        sequence = 6;
        board.resize(10, std::vector<Card*>(10, nullptr));
        grid = new Button * [10];
        for (int i = 0; i < 10; i++)
        {
            grid[i] = new Button[10]();
        }
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                flag[i][j] = 0;
                grid[i][j].button.setOutlineThickness(2.5); // Set outline thickness (5 pixels)
                grid[i][j].button.setOutlineColor(sf::Color::Black); // Set outline color
                if (i == 0 && j == 0)
                {
                    grid[i][j].button.setPosition({ 315,105 });
                    grid[i][j].button.setFillColor(sf::Color::Transparent);
                    grid[i][j].button.setSize({ 67,49 });
                }
                else if (i%2==0)
                {
                    if (j == 0)
                        grid[i][j].button.setPosition({ grid[i - 1][j].button.getPosition().x,grid[i - 1][j].button.getPosition().y + grid[i - 1][j].button.getSize().y });
                    else
                        grid[i][j].button.setPosition({ grid[i][j - 1].button.getPosition().x + grid[i][j - 1].button.getSize().x,grid[i][j - 1].button.getPosition().y });
                   
                        grid[i][j].button.setFillColor(sf::Color::Transparent);
                    grid[i][j].button.setSize({ 67,49 });
                }
                else if (i % 2 != 0)
                {
                    if(j==0)
                        grid[i][j].button.setPosition({ grid[i-1][j].button.getPosition().x,grid[i-1][j].button.getPosition().y + grid[i-1][j].button.getSize().y});
                    else
                        grid[i][j].button.setPosition({ grid[i][j-1].button.getPosition().x + grid[i][j-1].button.getSize().x,grid[i][j-1].button.getPosition().y });
                    grid[i][j].button.setFillColor(sf::Color::Transparent);

                    grid[i][j].button.setSize({ 67,49 });
                }
            }
        }
    }
    bool mouseover(RenderWindow& window)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (grid[i][j].mouseover(window))
                    return true;
            }
        }
        return false;
    }
    bool checkForSequences(int playerTurn, int& count) {
        // Check for 6 consecutive cards in a row (horizontal, vertical, or diagonal)
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                // Check horizontal
                if (j + sequence - 1 < 10) 
                {
                    bool horizontal = true;
                    for (int k = 0; k < sequence; ++k) {
                        if (i == 9 && j + k == 0)
                            continue;
                        if (flag[i][j + k] != playerTurn) {
                            horizontal = false;
                            break;
                        }
                    }
                    if (horizontal) 
                    {
                        for (int k = 0; k < sequence; ++k) {
                            if (i == 9 && j+k == 0)
                                continue;
                            flag[i][j + k] = playerTurn + 5;
                        }
                        count++;
                        return true;
                    }
                }
                // Check vertical
                if (i + sequence - 1 < 10) {
                    bool vertical = true;
                    for (int k = 0; k < sequence; ++k) 
                    {
                        if (i + k == 9 && j == 0)
                            continue;
                        if (flag[i + k][j] != playerTurn) {

                            vertical = false;
                            break;
                        }
                    }


                    if (vertical) {
                        for (int k = 0; k < sequence; ++k) {
                            if (i + k == 9 && j == 0)
                                continue;
                            flag[i + k][j] = playerTurn+5; // Mark pattern cells as 5
                        }
                        count++;
                        return true;
                    }
                }

                // Check diagonal (top-left to bottom-right)
                if (i + sequence - 1 < 10 && j + sequence - 1 < 10) {
                    bool diagonal = true;
                    for (int k = 0; k < sequence; ++k) {
                        if (i + k == 9 && j+k == 0)
                            continue;
                        if (flag[i + k][j + k] != playerTurn) {
                            diagonal = false;
                            break;
                        }
                    }
                    if (diagonal) {
                        for (int k = 0; k < sequence; ++k) {
                            if (i + k == 9 && j+k == 0)
                                continue;
                            flag[i + k][j + k] = playerTurn+5; // Mark pattern cells as 5
                        }
                        count++;
                        return true;
                    }
                }

                // Check reverse diagonal (bottom-left to top-right)
                if (i - sequence + 1 >= 0 && j + sequence - 1 < 10) {
                    bool reverseDiagonal = true;
                    for (int k = 0; k < sequence; ++k) {

                        if (i - k == 9 && j + k == 0)
                            continue;
                        if (flag[i - k][j + k] != playerTurn) {
                            reverseDiagonal = false;
                            break;
                        }
                    }
                    if (reverseDiagonal) {
                        for (int k = 0; k < sequence; ++k) {
                            if (i - k == 9 && j+k == 0)
                                continue;
                            flag[i - k][j + k] = playerTurn+5; // Mark pattern cells as 5
                        }
                        count++;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void setupBoard() {
        board[0][0] = new Card("W");      // Wild Card
        board[0][1] = new Card("10S");    // 10 of Spades
        board[0][2] = new Card("QS");     // Queen of Spades
        board[0][3] = new Card("KS");     // King of Spades
        board[0][4] = new Card("AS");     // Ace of Clubs
        board[0][5] = new Card("2D");     // 2 of Diamonds
        board[0][6] = new Card("3D");     // 3 of Diamonds
        board[0][7] = new Card("4D");     // 4 of Diamonds
        board[0][8] = new Card("5D");     // 5 of Diamonds
        board[0][9] = new Card("W");      // Wild Card

        board[1][0] = new Card("9S");     // 9 of Spades
        board[1][1] = new Card("10H");    // 10 of Hearts
        board[1][2] = new Card("9H");     // 9 of Hearts
        board[1][3] = new Card("8H");     // 8 of Hearts
        board[1][4] = new Card("7H");     // 7 of Hearts
        board[1][5] = new Card("6H");     // 6 of Hearts
        board[1][6] = new Card("5H");     // 5 of Hearts
        board[1][7] = new Card("4H");     // 4 of Hearts
        board[1][8] = new Card("3H");     // 3 of Hearts
        board[1][9] = new Card("6D");     // 6 of Diamonds

        board[2][0] = new Card("8S");     // 8 of Spades
        board[2][1] = new Card("QH");     // Queen of Hearts
        board[2][2] = new Card("7D");     // 7 of Diamonds
        board[2][3] = new Card("8D");     // 8 of Diamonds
        board[2][4] = new Card("9D");     // 9 of Diamonds
        board[2][5] = new Card("10D");    // 10 of Diamonds
        board[2][6] = new Card("QD");     // Queen of Diamonds
        board[2][7] = new Card("KD");     // King of Diamonds
        board[2][8] = new Card("2H");     // 2 of Hearts
        board[2][9] = new Card("7D");     // 7 of Diamonds

        board[3][0] = new Card("7S");     // 7 of Spades
        board[3][1] = new Card("KH");     // King of Hearts
        board[3][2] = new Card("6D");     // 6 of Diamonds
        board[3][3] = new Card("2C");     // 2 of Clubs
        board[3][4] = new Card("AH");     // Ace of Hearts
        board[3][5] = new Card("KH");     // King of Hearts
        board[3][6] = new Card("QH");     // Queen of Hearts
        board[3][7] = new Card("AD");     // Ace of Clubs
        board[3][8] = new Card("2S");     // 2 of Spades
        board[3][9] = new Card("8D");     // 8 of Diamonds

        board[4][0] = new Card("6S");     // 6 of Spades
        board[4][1] = new Card("AH");     // Ace of Hearts
        board[4][2] = new Card("5D");     // 5 of Diamonds
        board[4][3] = new Card("3C");     // 3 of Clubs
        board[4][4] = new Card("4H");     // 4 of Hearts
        board[4][5] = new Card("3H");     // 3 of Hearts
        board[4][6] = new Card("10H");    // 10 of Hearts
        board[4][7] = new Card("AC");     // Ace of Clubs
        board[4][8] = new Card("3S");     // 3 of Spades
        board[4][9] = new Card("9D");     // 9 of Diamonds

        board[5][0] = new Card("5S");     // 5 of Spades
        board[5][1] = new Card("2C");     // 2 of Clubs
        board[5][2] = new Card("4D");     // 4 of Diamonds
        board[5][3] = new Card("4C");     // 4 of Clubs
        board[5][4] = new Card("5H");     // 5 of Hearts
        board[5][5] = new Card("2H");     // 2 of Hearts
        board[5][6] = new Card("9H");     // 9 of Hearts
        board[5][7] = new Card("KC");     // King of Clubs
        board[5][8] = new Card("4S");     // 4 of Spades
        board[5][9] = new Card("10D");    // 10 of Diamonds

        board[6][0] = new Card("4S");     // 4 of Spades
        board[6][1] = new Card("3C");     // 3 of Clubs
        board[6][2] = new Card("3D");     // 3 of Diamonds
        board[6][3] = new Card("5C");     // 5 of Clubs
        board[6][4] = new Card("6H");     // 6 of Hearts
        board[6][5] = new Card("7H");     // 7 of Hearts
        board[6][6] = new Card("8H");     // 8 of Hearts
        board[6][7] = new Card("QC");     // Queen of Clubs
        board[6][8] = new Card("5S");     // 5 of Spades
        board[6][9] = new Card("QD");     // Queen of Diamonds

        board[7][0] = new Card("3S");     // 3 of Spades
        board[7][1] = new Card("4C");     // 4 of Clubs
        board[7][2] = new Card("2D");     // 2 of Diamonds
        board[7][3] = new Card("6C");     // 6 of Clubs
        board[7][4] = new Card("7C");     // 7 of Clubs
        board[7][5] = new Card("9C");     // 9 of Clubs
        board[7][6] = new Card("9C");     // 9 of Clubs
        board[7][7] = new Card("10C");    // 10 of Clubs
        board[7][8] = new Card("6S");     // 6 of Spades
        board[7][9] = new Card("KD");     // King of Diamonds

        board[8][0] = new Card("2S");     // 2 of Spades
        board[8][1] = new Card("5C");     // 5 of Clubs
        board[8][2] = new Card("AS");     // Ace of Spades
        board[8][3] = new Card("KS");     // King of Spades
        board[8][4] = new Card("QS");     // Queen of Spades
        board[8][5] = new Card("10S");    // 10 of Spades
        board[8][6] = new Card("9S");     // 9 of Spades
        board[8][7] = new Card("8S");     // 8 of Spades
        board[8][8] = new Card("7S");     // 7 of Spades
        board[8][9] = new Card("AD");     // Ace of Diamonds

        board[9][0] = new Card("W");      // Wild Card
        board[9][1] = new Card("6C");     // 6 of Clubs
        board[9][2] = new Card("7C");     // 7 of Clubs
        board[9][3] = new Card("8C");     // 8 of Clubs
        board[9][4] = new Card("9C");     // 9 of Clubs
        board[9][5] = new Card("10C");    // 10 of Clubs
        board[9][6] = new Card("QC");     // Queen of Clubs
        board[9][7] = new Card("KC");     // King of Clubs
        board[9][8] = new Card("AC");     // Ace of Clubs
        board[9][9] = new Card("W");      // Wild Card
    }

    void printBoard() {
        for (const auto& row : board) {
            for (const auto& card : row) {
                if (card) {
                    std::cout << card->value << "\t";
                }
                else {
                    std::cout << "Empty\t";
                }
            }
            std::cout << std::endl;
        }
    }

    ~Board() {
        for (auto& row : board) {
            for (auto& card : row) {
                delete card;
            }
        }
    }
    void draw(RenderWindow& window)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                grid[i][j].draw(window);
            }
        }
    }
};

