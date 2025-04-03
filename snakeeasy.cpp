#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;
bool gameover;
const int width = 20, hight = 20;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100], ntail;
enum ctrl
{
    stop = 0,
    up,
    down,
    Left,
    Right
};
ctrl dir;
void setup()
{
    score = 0;
    gameover = false;
    x = 20 / 2;
    y = 20 / 2;
    srand(time(0));
    fruitx = rand() % (width - 2);
    fruity = rand() % (hight - 2);
    dir = stop;
}
void drow()
{
    system("CLS");
    for (int i = 0; i < width; i++)
    {
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width - 1)
            {
                cout << "|";
            }
            else if (i == x && j == y)
            {
                // for snake head
                cout << "o";
            }
            else if (i == fruitx && j == fruity)
            {
                // for fruit
                cout << "*";
            }
            else
                {
                 bool print= false;
                 for(int k=0; k<ntail; k++ )
                 {
                    if(j==taily[k]&& i==tailx[k])
                    {
                        // for growth of snake;
                        cout<<"o";
                        print= true;
                    }
                 }   
                    if(!print)
                    cout << " ";
                }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
    {
        cout << "_";
    }
    cout << endl;
    cout<<endl;
    cout<<"score : "<< score<<endl;
}
void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = up;
            break;
        case 's':
            dir = down;
            break;
        case 'a':
            dir = Left;
            break;
        case 'd':
            dir = Right;
            break;
        default:
            break;
        }
    }
}
void logic()
{
    int prevx=tailx[0];
    int prevy=taily[0];
    tailx[0]=x;
    taily[0]=y;
    int prev2x, prev2y;
    for(int i=1; i<ntail; i++)
    {
        prev2x=tailx[i];
        prev2y=taily[i];
        tailx[i]= prevx;
        taily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;

    }

    switch (dir)
    {
    case up:
        x--;
        break;
    case down:
        x++;
        break;
    case Left:
        y--;
        break;
    case Right:
        y++;
        break;
    default:
        break;
    }
    if (x < 0 || x > width || y < 0 || y > hight)
    {
        gameover = true;
    }
    for(int i=0; i<ntail; i++)
    {
        if(x==tailx[i]&& y==taily[i]){
            gameover=true;
        }
    }
    if (x == fruitx && y == fruity)
    {
        score = score + 1;
        srand(time(0));
        fruitx = rand() % (width - 2);
        fruity = rand() % (hight - 2);
        ntail++;
    }
}

int main()
{

    setup();
    while (!gameover)
    {
        drow();
        input();
        logic();
        Sleep(40);
    }


    return 0;
}