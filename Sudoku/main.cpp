#include <iostream>
#include <array>
#include <random>
#include <string>
#include <bits/stdc++.h>
#include <iterator>
using namespace std;

class Grid{
private:
    array<array<string, 9>, 9> grid;
public:
    Grid(){};

    //Set the initial state of the Grid
    //Grid is 9x9
    void set_grid(){
        for(int i = 0; i < grid.size(); i++){
            for(int j = 0; j < grid.size(); j++){
                grid[i][j] = "-";
            }
        }
    }
    void set_numbers(int generation_amt){
        int ran_pos_x, ran_pos_y, ran_num;

        //Generate random numbers for positions on the Grid
        random_device pos_rd; //obtain a random number from hardware
        mt19937 pos_eng(pos_rd()); //seed the generator
        uniform_int_distribution<> pos_distr(0, 8); //generate numbers { 0 - 8 } pos

        //Generate random numbers for numbers on the Grid
        random_device num_rd; //obtain a random number from hardware
        mt19937 num_eng(num_rd()); //seed the generator
        uniform_int_distribution<> num_distr(1, 9); //generate numbers { 1 - 9 } num

        ran_pos_x = pos_distr(pos_eng); //Initial position generation
        ran_pos_y = pos_distr(pos_eng); //Initial position generation
        ran_num = num_distr(num_eng); //Initial number generation

        int gen_amt = generation_amt; //Amount to be generated
        int itr = 0; //Iteration loop control

        while(itr < gen_amt){
            //If the position in the grid has not been taken
            if(grid[ran_pos_x][ran_pos_y] == "-"){
                //Set that position to a random number
                grid[ran_pos_x][ran_pos_y] = std::to_string(ran_num);
                //Generate another random number
                ran_num = num_distr(num_eng);
                //Generate another random position
                ran_pos_x = pos_distr(pos_eng);
                ran_pos_y = pos_distr(pos_eng);
            }
            //Else if that position has been taken
            else{
                //Generate another random position
                ran_pos_x = pos_distr(pos_eng);
                ran_pos_y = pos_distr(pos_eng);
                //And place a random number on the newly generated position
                grid[ran_pos_x][ran_pos_y] = std::to_string(ran_num);
                //Generate new number
                ran_num = num_distr(num_eng);
                //Generate new position
                ran_pos_x = pos_distr(pos_eng);
                ran_pos_y = pos_distr(pos_eng);
            }
            itr++;
        }

        unordered_set<string> string_set;

        //Check for repeated numbers in a row

        for(int i = 0; i < grid.size(); i++){
            string_set.clear(); //Clear set for each row
            for(int j = 0; j < grid.size(); j++){
                if(string_set.find(grid[i][j]) == string_set.end() && grid[i][j] != "-"){
                    string_set.insert(grid[i][j]);
                }
                else{
                    grid[i][j] = "-";
                    //grid[i][j] = std::to_string(ran_num);
                   //ran_num = num_distr(num_eng);
                }
            }
        }


        //Check for repeated numbers in a column
        //While loop?
        string_set.clear(); //Clear set for column loop

        int i = 0;
        int test = 0;
        while(true){
            if(i == 9){
                test++;
                i=0;
                string_set.clear(); //Clear set for each column
            }
            if(test == 8 && i == 8){
                break;
            }
            if(string_set.find(grid[i][test]) == string_set.end() && grid[i][test] != "-"){
                string_set.insert(grid[i][test]);
            }
            else{
                grid[i][test] = "-";
                //grid[i][test] = std::to_string(ran_num);
                //ran_num = num_distr(num_eng);
            }
            i++;
        }
    }
    //Place a number on the grid with given x and y coordinates
    void place_num_at(int pos_x, int pos_y, int num){
        grid[pos_x][pos_y] = std::to_string(num);
    }
    bool check_win(){

    }
    //Print out the representation of the Grid
    void to_string(){
        for(int i = 0; i < grid.size(); i++){
            if(i == 3){
                cout << "-------------------------------------------" << "\n";
            }
            if(i == 6){
                cout << "-------------------------------------------" << "\n";
            }
            if(i == 9){
                cout << "-------------------------------------------" << "\n";
            }
            for(int j = 0; j < grid.size(); j++){
                cout << grid[i][j] << "   ";
                if(j == 2){
                    cout << "|  ";
                }
                if(j == 5){
                    cout << "|  ";
                }
                if(j == 8){
                    cout << "|  ";
                }
            }
            cout << "\n";
        }
    }
};

int RUNNING = 1;

int main() {
    Grid sudoku_board;
    sudoku_board.set_grid();

    int diff;
    cout << "Please enter a difficulty num from { 10 - 50 }: ";
    cin >> diff;
    sudoku_board.set_numbers(diff);

    while(RUNNING){
        int x,y,num;
        sudoku_board.to_string();
        cout << "Please enter pos_x: ";
        cin >> x;
        cout << "Please enter pos_y: ";
        cin >> y;
        cout << "Please enter num: ";
        cin >> num;
        sudoku_board.place_num_at(x, y, num);
    }
    return 0;
}