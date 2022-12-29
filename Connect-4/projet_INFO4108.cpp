#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <time.h>

using namespace std;

int col_max = 7;
int lig_max = 6;
vector<vector<int>> b(col_max, vector<int>(lig_max));
int d;

void insert(vector<vector<int>> &b, int c)
{
  ++d;

         if(c < 0) return;
         if(c > 6) return;

        for (int i = 5; i >= 0; i--)
        {

                if (b[c][i] == 0)
                 {

                   if((d % 2) == 0) {b[c][i] = 2; break;}
                   else {b[c][i] = 1; break;}
                  }
        }
                for (unsigned int i = 1; i < 7; i++) {
                        cout << " " << i;
                }
                cout << endl << "---------------" << endl;
                for (unsigned int r = 0; r < lig_max; r++)
                {
                        for (unsigned int c = 0; c < col_max; c++)
                        {
                                cout << "|";
                                switch ((b[c][r])) {
                                case 0: cout << " "; break;
                                case 1: cout << "O"; break;
                                case 2: cout << "X"; break;
                                }
                                if (c + 1 == 7) { cout << "|"; }
                        }
                        cout << endl;
                }
                cout << "---------------" << endl;
                cout << endl;

}

bool verif_vic( vector<vector<int>> &tab )
{
        for (unsigned int i = 0; i < lig_max; i++)
        {
                for (unsigned int j = 0; j < col_max; j++)
                {
                        if (tab[j][i] == 1 && tab[j + 1][i + 1] == 1 && tab[j + 2][>                        {
                                cout << "\nVous avez perdu" << endl;
                                return true;
                        }
                        if (tab[j][i] == 1 && tab[j + 1][i - 1] == 1 && tab[j + 2][>                        {
                                cout << "\nVous avez perdu" << endl;
                                return true;
                        }
                        if (tab[j][i] == 2 && tab[j + 1][i - 1] == 2 && tab[j + 2][>                        {
                                cout << "\nVous avez gagné !!!" << endl;
                                return true;
                        }
                        else if (tab[j][i] == 2 && tab[j - 1][i - 1] == 2 && tab[j >                        {
                                cout << "\nVous avez gagné !!!" << endl;
                                return true;
                        }
                        else if (tab[j][i] == 1 && tab[j][i - 1] == 1 && tab[j][i ->                        {
                                cout << "\nVous avez perdu" << endl;
                                return true;
                        }
                        else if (tab[j][i] == 1 && tab[j - 1][i] == 1 && tab[j - 2]>                        {
                                cout << "\nVous avez perdu" << endl;
                                return true;
                        }
                        else if (tab[j][i] == 2 && tab[j][i - 1] == 2 && tab[j][i ->                        {
                                cout << "\nVous avez gagné !!!" << endl;
                                return true;
                        }
                        else if (tab[j][i] == 2 && tab[j - 1][i] == 2 && tab[j - 2]>                        {
                                cout << "\nVous avez gagné !!!" << endl;
                                return true;
                        }
                }
        }

  return false;
}

int main()
{

// J'ai utilise trois tube qui communique ensemble le premier fils qui est
// le joueur ecrit en envoit au deuxieme processus qui est l'ordinateur et
// dans ce processus qui l'ecrit dans un troisieme tube et le renvoit au pere

  int x;
  int c;
  int me,ai;
  int fd[3][2];

  for(unsigned int i=0; i<3; i++)
  {
     if(pipe(fd[i]) < 0) return 1;
      else  pipe(fd[i]);
  }

  me = fork();
  if(me < 0) return 1;
  if(me == 0)
  {
     close(fd[0][1]);
     close(fd[1][0]);
     close(fd[2][0]);
     close(fd[2][1]);

      if(read(fd[0][0], &c, 1) < 0) return 3;

      cout << " A vous de jouez !! " << endl;
      cin >> c;


    if(write(fd[1][1], &c, 1) < 0) return 4;
      exit(1);

     close(fd[0][0]);
     close(fd[1][1]);

     return 0;
  }

  ai = fork();
  if(ai < 0) return 2;
  if(ai == 0)
  {
     close(fd[0][0]);
     close(fd[0][1]);
     close(fd[1][1]);
     close(fd[2][0]);

      if(read(fd[1][0], &c, 1) < 0) return 5;
      if(write(fd[2][1], &c, 1) < 0) return 6;

      c = rand() % 6;

      if(write(fd[2][1], &c, 1) < 0) return 6;

        exit(2);

     close(fd[1][0]);
     close(fd[2][1]);

     return 0;
  }

     cout << " " << " " << getpid() << endl;

     close(fd[0][0]);
     close(fd[1][0]);
     close(fd[1][1]);
     close(fd[2][1]);

    if(write(fd[0][1], &c, 1) < 0) return 7;

    while(read(fd[2][0], &c, 1) > 0)
     {
        insert(b,c);
    }
       cout << endl;

     close(fd[0][1]);
     close(fd[2][0]);

    waitpid(me, NULL, 0);
    waitpid(ai, NULL, 0);

        return 0;
}
