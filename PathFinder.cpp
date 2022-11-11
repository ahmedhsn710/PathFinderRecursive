#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;


// globally defining size for matrix
int size = 7;

// vector string to store all the results
vector <string> result;

// making a temporary matrix to keep track of already traveled points
int** visited { new int*[size] };

// populates a matrix with random 1 and 0
void populatematrix(int **arr, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {

            int n = rand();

            // the value 12000 is for calculated from hit and trial which gives approximately 65 % probability of 1
            if (n > 12000){
                arr[i][j]=1;
            }
            else {
                arr[i][j]=0;
            }
        }
    }
}

// prints a matrix
void printmatrix(int **arr, int size){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}

// draws a maze from a matrix and starting and finish points
void draw(int **arr, int size, int sx, int sy, int fx, int fy){

    for (int k = 0; k < size+2; k++) cout<<" - ";
    cout<<endl;

    for (int i = 0; i < size; i++) {
        cout<<" | ";
        for (int j = 0; j < size; j++) {
            if (arr[i][j]==0){
                cout<<" # ";
            }
            else {
                // print F for end point
                if (i==fx and j == fy) cout<<" F ";
                // print S for starting point
                else if (i==sx and j == sy) cout<<" S ";
                // print empty space for 1
                else if (arr[i][j] == 1) cout<<"   ";
                // print . mean included in path
                else if (arr[i][j] == 3) cout<<" . ";
                else cout<<" "<<arr[i][j]<<" ";
            }
        }
        cout<<" | "<<endl;
    }
    for (int k = 0; k < size+2; k++) cout<<" - ";
    cout<<endl<<endl<<endl;
}

// prints the all the possible paths from starting point to end point
bool findPath(int x, int y, int endX, int endY, int** arr, int size, string ans = "", bool print = false)
{
    if (x == endX and y == endY){
        if (print) {
            cout << result.size() << ". " << ans << endl;
            draw(arr, size, x, y, endX, endY);
        }
        result.push_back(ans);
    }

    // means the point is traveled
    arr[x][y] = 3;

    // downward
    if (x + 1 < size && !visited[x + 1][y] && arr[x + 1][y] == 1) {
        visited[x][y] = 1;
        findPath(x + 1, y, endX, endY, arr, size, ans + 'D');
        visited[x][y] = 0;
    }

    // right
    if (y + 1 < size && !visited[x][y+1] && arr[x][y+1] == 1) {
        visited[x][y] = 1;
        findPath(x, y + 1, endX, endY, arr, size, ans + 'R');
        visited[x][y] = 0;
    }

    // upward
    if (x - 1 > 0 && !visited[x - 1][y] && arr[x - 1][y] == 1) {
        visited[x][y] = 1;
        findPath(x - 1, y, endX, endY, arr, size, ans + 'U');
        visited[x][y] = 0;
    }

    // left
    if (y-1 >= 0 && !visited[x][y-1] && arr[x][y-1] == 1) {
        visited[x][y] = 1;
        findPath(x, y - 1, endX, endY, arr, size, ans + 'L');
        visited[x][y] = 0;
    }

    // backtracking to parent
    arr[x][y] =1;
    return result.size();
}

// return a vector with all the shortest paths
vector<string> shortpath(vector<string> str){
    vector<string> ret;
    if (!str.empty()) {
        string min = str[0];
        for (auto & i : str) {
            if (i.size() < min.size()) min = i;
        }

        for (auto & i : str) {
            if (i.size() == min.size()) ret.push_back(min);
        }
    }
    return ret;
}

// return a vector with all the longest paths
vector<string> longpath(vector<string> str){
    vector<string> ret;
    if (!str.empty()) {
        string max = str[0];
        for (auto & i : str) {
            if (i.size() > max.size()) max = i;
        }

        for (auto & i : str) {
            if (i.size() == max.size()) ret.push_back(max);
        }

    }
    return ret;
}

// prints a vector
void printvector(vector<string> str) {
    if (str.empty())
        cout << "No Solution Possible !"<<endl;
    else {
        for (int i = 0; i < str.size(); i++)
            cout << i << ". " << str[i] << endl;
        cout << endl;
    }
}

/*
int main(){

    // seeding random number generator
    srand(time(0));

    // making a dynamic 2d square array and populating it with random 0s and 1s
    int** matrix { new int*[size] }; // allocate an array of int pointers — these are rows
    for (int count =0; count < size; count++){
        matrix[count] = new int[size]; // these are our columns
    }
    populatematrix(matrix, size);

    // initializing visited matrix with 0 entries
    for (int count =0; count < size; count++){
        visited[count] = new int[size]; // these are our columns
        for (int i = 0; i < size; i++) {
            visited[count][i] = 0;
        }
    }


    // selecting random starting point
    select:
    int startx =rand()%size;
    int starty =rand()%size;
    if (matrix[startx][starty]==0){
        goto select;
    }

    // selecting random finish point
    int finishx =rand()%size;
    int finishy =rand()%size;

    // the algo woks if start is greater than finish
    if (matrix[finishx][finishy]==0 or finishx <= startx or finishy <= starty){
        goto select;
    }

    cout<<"The Given maze is "<<endl;
    draw(matrix, size, startx, starty, finishx, finishy);

    cout<<"The Possible solution are : "<<endl;
    findPath(startx, starty, finishx, finishy, matrix, size);
    printvector(result);

    cout<<"The total possible paths from start to finish are : "<<result.size()<<endl;

    cout<<"The shortest path is : "<<endl;
    printvector(shortpath(result));

    cout<<"The longest path is : "<<endl;
    printvector(longpath(result));

    return 0;
}*/