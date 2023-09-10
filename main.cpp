//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Move
{
    int row,col;
};
class Board
{
private:
    vector<vector<string>> arr{
            {"  ","G1","G2","G3","  "},
            {"R1","  ","  ","  ","  "},
            {"R2","  ","  ","  ","  "},
            {"R3","  ","  ","  ","  "},
            {"  ","  ","  ","  ","  "}
            };
    string last_move;
    Move lastMoveRC;
    int step;
    string umove;
public:
    Board(){}
    void printB()
    {
        for (int i=0;i<5;i++)
        {
            for (int j=0;j<5;j++)
            {
                cout << "|" <<arr[i][j] << "|" ;
            }
            cout <<endl;
        }
        cout << endl;
    }
    string element(int i, int j)
    {
        return arr[i][j];
    }
    void Move(string s)
    {
        string a = s;
        umove = s;
        if (valid_move(s))
        {
            if (a[0]=='G')
            {
                for (int i=0;i<4;i++)
                {
                    for (int j=1;j<4;j++)
                    {
                        if (arr[i][j]==a)
                        {
                            if (arr[i+1][j]=="  ")
                            {
                                arr[i][j]="  ";
                                arr[i+1][j]=a;
                                last_move="i"+to_string(i+1);
                                step =1;
                                lastMoveRC.row = i+1;
                                lastMoveRC.col = j;
                                a="d";
                                break;
                            }
                            else if (arr[i+1][j]!="  " && arr[i+2][j]=="  ")
                            {
                                arr[i][j]="  ";
                                arr[i+2][j]=a;
                                last_move="i"+to_string(i+2);
                                step = 2;
                                lastMoveRC.row = i+2;
                                lastMoveRC.col = j;
                                a="d";
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    if (a=="d")
                    {
                        break;
                    }
                }
            }
            else if (a[0]=='R')
            {
                for (int i=1;i<4;i++)
                {
                    for (int j=0;j<4;j++)
                    {
                        if (arr[i][j]==a)
                        {
                            if (arr[i][j+1]=="  ")
                            {
                                arr[i][j]="  ";
                                arr[i][j+1]=a;
                                last_move="j"+to_string(j+1);
                                step = 1;
                                lastMoveRC.row = i;
                                lastMoveRC.col = j+1;
                                a="d";
                                break;
                            }
                            else if (arr[i][j+1]!="  " && arr[i][j+2]=="  ")
                            {
                                arr[i][j]="  ";
                                arr[i][j+2]=a;
                                last_move="j"+to_string(j+2);
                                step = 2;
                                lastMoveRC.row = i;
                                lastMoveRC.col = j+2;
                                a="d";
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    if (a=="d")
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            cout << "Invalid Move!\n";
        }
    }

    void Undo()
    {
        if (last_move[0]=='i')
        {
            arr[lastMoveRC.row][lastMoveRC.col] = "  ";
            arr[lastMoveRC.row-step][lastMoveRC.col] =umove ;
        }
        else if (last_move[0]=='j')
        {
            arr[lastMoveRC.row][lastMoveRC.col] = "  ";
            arr[lastMoveRC.row][lastMoveRC.col-step] =umove;
        }
    }

    bool Point()
    {
        if (last_move=="j4"||last_move=="i4")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool valid_move(string a)
    {
        if (a[0]=='G'||a[0]=='R')
        {
            for (int i=0;i<5;i++)
            {
                for (int j=0;j<5;j++)
                {
                    if (arr[i][j]==a)
                    {
                        if (i==4||j==4)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }

    }

    int check_end()
    {
        int c1=0,c2=0;
        for (int j=1;j<5;j++)
        {
            if (arr[4][j]!="  ")
            {
                c1++;
            }
        }
        if (c1==3)
        {
            return 1;
        }
        for (int i=1;i<5;i++)
        {
            if (arr[i][4]!="  ")
            {
                c2++;
            }
        }
        if (c1==3)
        {
            return 1;
        }
        else if (c2==3)
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }

    bool Player1_win()
    {
        int c1=0;
        for (int j=1;j<5;j++)
        {
            if (arr[4][j]!="  ")
            {
                c1++;
            }
        }
        if (c1==3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    bool Player2_win()
    {
        int c1=0;
        for (int i=1;i<5;i++)
        {
            if (arr[i][4]!="  ")
            {
                c1++;
            }
        }
        if (c1==3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

};

class Player
{
private:
    string name;
    int score;
public:
    Player()
    {
        score=0;
    }
    Player(string n)
    {
        name = n;
        score = 0;
    }
    void set_name(string n)
    {
        name = n;
    }
    void inc_score()
    {
        score++;
    }
    string get_name()
    {
        return name;
    }
    int get_score()
    {
        return score;
    }
};


class AI
{
private:
    Board b;
    int turn;
public:
    AI()
    {
        turn = 1;
    }
    void Turn()
    {
        if (turn==1)
        {
            turn=2;
        }
        else
        {
            turn=1;
        }
    }
    void play()
    {
        Player A("Player 1");
        Player B("AI");
        string name;
        cout << "       Welcome to Rocket game\n\n";
        cout << "Enter your Name : ";
        cin >> name;
        A.set_name(name);
        string mv;
        b.printB();
        while(true)
        {

            Move bm = findBestMove(b);
            mv = b.element(bm.row, bm.col);
            b.Move(mv);
            if (b.Point())
            {
                B.inc_score();
            }
            b.printB();
            cout << name << " score : " << A.get_score() << endl;
            cout << "AI" << " score : " << B.get_score() << endl;
            if (b.check_end()==1)
            {
                cout << "AI" << " Win!!\n\n";
                break;
            }
            Turn();

            //Player Turn ...............
            while(true)
            {
                cout << name << " you want to move (R1 - R2 - R3): ";
                cin >> mv;
                if (mv == "R1" || mv == "R2" || mv == "R3" && b.valid_move(mv) )
                {
                    b.Move(mv);
                    if (b.Point())
                    {
                        A.inc_score();
                    }
                    break;
                }
                else
                {
                    cout << "Invalid input!!\n";
                }
            }
            b.printB();
            cout << name << " score : " << A.get_score() << endl;
            cout << "AI" << " score : " << B.get_score() << endl;
            if (b.check_end()==2)
            {
                cout << name << " Win!!\n\n";
                break;
            }
            

            //Computer Turn ...............

            



        }
    }

    int Evaluate(Board b)
    {
        if (b.Player1_win())
        {
            return -10;
        }
        else if (b.Player2_win())
        {
            return 10;
        }
        else
        {
            return 0;
        }
    }
    int MIN = -1000;
    int MAX =  1000;

    int minimax(Board b, int depth, bool ismax,int alpha, int beta)
    {

        int score = Evaluate(b);

        //BASE CASE

        // If Maximizer has won the game return his/her
        // evaluated score
        if (score == 10)
        {
            return score-depth;
        }

        // If Minimizer has won the game return his/her
        // evaluated score
        if (score == -10)
        {
            return score+depth;
        }

        // If this maximizer's move
        if (ismax)
        {
            int best = -1000;
            int c=1;
            // Traverse all cells
            for (int i = 0; i<4; i++)
            {
                for (int j = 1; j<4; j++)
                {
                    if (b.element(i,j)[0]=='G')
                    {
                        // Check if cell is empty
                        if (b.element(i+1,j)=="  ")
                        {
                            if (b.valid_move("G"+to_string(j)))
                            {
                                // Make the move
                                b.Move("G"+to_string(j));

                                // Call minimax recursively and choose
                                // the maximum value
                                best = max( best,
                                    minimax(b, depth+1, !ismax,alpha,beta) );
                                alpha = max(best,alpha);
                                // Undo the move
                                b.Undo();

                            }
                            else
                            {
                            	continue;
                            }
                        }

                        else if (b.element(i+1 ,j)!="  " && b.element(i+2 , j)=="  ")
                        {
                            if (b.valid_move("G"+to_string(j)))
                            {
                                // Make the move
                                b.Move("G"+to_string(j));

                                // Call minimax recursively and choose
                                // the maximum value
                                best = max( best,
                                    minimax(b, depth+1, !ismax,alpha,beta) );
                                alpha = max(alpha,best);
                                // Undo the move
                                b.Undo();

                            }
                            else
                            {
                            	continue;
                            }
                        }


                    }
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
                if (beta <= alpha)
                {
                    break;
                }
            }
            return best;
        }

        // If this minimizer's move
        else if (!ismax)
        {
            int best = 1000;
            static int c=1;
            // Traverse all cells
            for (int i = 1; i<4; i++)
            {
                for (int j = 0; j<4; j++)
                {
                    if (b.element(i,j)[0]=='R')
                    {
                        // Check if cell is empty
                        if (b.element(i,j+1)=="  ")
                        {
                            if (b.valid_move("R"+to_string(i)))
                            {
                                // Make the move
                                b.Move("R"+to_string(i));

                                // Call minimax recursively and choose
                                // the maximum value
                                best = min( best,
                                    minimax(b, depth+1, ismax,alpha,beta) );
                                beta = min(best,beta);
                                // Undo the move
                                b.Undo();

                            }
                        }

                        else if (b.element(i,j+1) == "  " && b.element(i,j+2)=="  ")
                        {
                            if (b.valid_move("R"+to_string(i)))
                            {
                                // Make the move
                                b.Move("R"+to_string(i));

                                // Call minimax recursively and choose
                                // the maximum value
                                best = min( best,
                                    minimax(b, depth+1, ismax,alpha,beta) );
                                beta = min(best,beta);
                                // Undo the move
                                b.Undo();
                            }
                        }
                        c++;

                    }
                    if (beta <= alpha)
                    {
                        break;
                    }
                }
                if (beta <= alpha)
                {
                    break;
                }
            }
            return best;
        }
    }

    Move findBestMove(Board b)
    {
        int bestVal = -1000;
        Move bestMove;
        bestMove.row = -1;
        bestMove.col = -1;
        int c=1;
        // Traverse all cells, evaluate minimax function for
        // all empty cells. And return the cell with optimal
        // value.
        for (int i = 0; i<4; i++)
        {
            for (int j = 1; j<4; j++)
            {

                if (b.element(i,j)[0]=='G')
                {
                    if (b.valid_move("G"+to_string(j)))
                    {
                        if (!(b.element(i+1,j)!= "  " && b.element(i+2,j)!= "  "))
                        {
                            // Make the move
                            b.Move("G"+to_string(j));

                            // compute evaluation function for this
                            // move.
                            int moveVal = minimax(b, 0, true,MIN,MAX);

                            // Undo the move
                            b.Undo();

                            // If the value of the current move is
                            // more than the best value, then update
                            // best/
                            if (moveVal > bestVal)
                            {
                                bestMove.row = i;
                                bestMove.col = j;
                                bestVal = moveVal;
                            }

                        }
                    }
                    c++;
                }

            }
        }

        printf("The value of the best Move is : %d\n\n",
                bestVal);

        return bestMove;
    }
};


int main()
{
    AI m;
    m.play();
    return 0;
}
