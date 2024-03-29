
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "picross.h"

void carregar_dades(picross_t *p)
{
    FILE * fit;
    fit = fopen ("input.txt", "r");
    int i, j;
    if (fit== NULL)
    {
        printf("Error al obrir el fitxer\n");
    }
    else
    {
        fscanf(fit,  "%d", &p->max_f);
        fscanf(fit,  "%d", &p->max_c);
        fscanf(fit,  "%d", &p->max_errors);

              for (i=0; i< p->max_f; i++)
               {
                   for (j=0; j< p->max_c; j++)
                   {
                       fscanf(fit, "%d", &p->taula[i][j]);
                      // printf("%d ", p->taula[i][j]);
                   }
               }
    }

}
void taula_adalt(picross_t *p)
{
     int x, y, j, i, comptador;

     p->n = p->max_f/2+1;
//COMPTADOR DE LES COLUMNES AMB ELS RESULTATS
           for (x=0; x< p->max_f; x++)
            {
                for (y=0; y<p->max_c; y++)
                {
                    p->taula1[x][y]= 0;
                }
            }

            comptador=0;
            x=0;  y=0;
            for (j=0; j< p->max_c+1; j++)
            {
               // comptador=0;
                x= p->n;
                for (i=0; i<p->max_f+1; i++)
                {
                    if(p->taula[i][j]==1)
                    {
                        comptador++;
                    }
                    else
                    {
                        if (comptador!=0)
                        {
                            p->taula1[x][y]= comptador;
                            x--;
                            comptador=0;
                        }
                    }
                }
                y++;
            }
            //PRINTEM ELS RESULTATS

           for (x= p->n; x>0; x--)
            {
                printf("\n");
                for(int k=0; k< p->n+2; k++ )
                {
                     printf(" ");
                }
                for(y=0; y<p->max_c; y++)
                {
                    if (p->taula1[x][y]!=0)
                    {
                        printf("%d ", p->taula1[x][y]);
                    }
                    else
                    {
                        printf("  ");
                    }
                }
             }
}
void iniciar_taula_respostes(picross_t *p)
{
       for (int i=0; i<p->max_f; i++)
            {
                for (int j=0; j< p->max_c+((p->n)+1); j++)
                {
                    p->taula_respostes[i][j]='X'; //omple tota la taula amb el car�cter X
                }

            }
}
void fer_taula(picross_t *p)
{
    //GUARDEM ZEROS A LA TAULA//
        int x, y, i, j, comptador;
              for ( x=0; x< p->max_f; x++)
            {
                for ( y=0; y<p->max_c; y++)
                {
                    p->taula2[x][y]= 0;
                }
            }
//COMPTADOR DEL RESULTAT DE LES COLUMNES
            comptador=0;
             x=0;
             y=0;
             for ( i=0; i < p->max_f+1; i++)
            {

                y=0;
                for ( j=0; j < p->max_c+1; j++)
                {
                    if(p->taula[i][j]==1)
                    {
                        comptador++;
                    }
                    else
                    {
                        if (comptador!=0)
                        {
                            p->taula2[x][y]= comptador;
                            y++;
                            comptador=0;
                        }
                    }
                }
                x++;
            }
}
void imprimir_taula_respostes(picross_t *p)
{

            int i,j,x,y;
            printf("\n");
            i=0;
             for (x=0; x<p->max_f; x++)
            {
                j=0;
                for ( y=0; y<p->max_c+p->n+1; y++)
                {
                    if (p->taula2[x][y]!= 0)
                    {
                        if(y< p->n)
                        {
                           printf ("%d", p->taula2[x][y]);
                        }
                    }
                     else
                    {
                        printf(" ");
                        if(y> p->n)
                        {
                            printf("%c", p->taula_respostes[i][j]);
                            j++;
                        }
                    }
                }
                printf("\n");
            i++;
            }
}

void pregunta_posicio(picross_t *p)
{
    printf("\nTria una fila del 1 i al %d\n", p->max_f);
    scanf("%d", &p->fila);
    while ((p->fila<1)||(p->fila> p->max_f))
    {
        printf("\nFila no valida, tria una fila del 1 i al %d\n", p->max_f);
        scanf("%d", &p->fila);
    }

    p->fila= p->fila-1;

    printf("\nTria una columna del 1 i al %d\n", p->max_c);
    scanf("%d", &p->columna);
    while ((p->columna<1)||(p->columna>p->max_c))
    {
        printf("\nColumna no valida, tria una columna del 1 i al %d\n", p->max_c);
        scanf("%d", &p->columna);
    }
    p->columna= p->columna-1;
}

bool posicio_omplerta (picross_t *p)
{
    bool omplert=false;

    if ((p->taula_respostes[p->fila][p->columna]=='0') || (p->taula_respostes[p->fila][p->columna]=='1'))
    {
        omplert=true;
    }

    return omplert;
}

void pregunta_resposta(picross_t *p)
{

    printf("\nEscriu la teva resposta\n");
    scanf("%d", &p->resposta);
    while ((p->resposta!=0)&&(p->resposta!=1))
    {
        printf("\nResposta no valida, recorda que la resposta nomes pot ser un 1 o un 0\n");
        scanf("%d", &p->resposta);
    }
}

bool resposta_ok(picross_t *p)
{
    bool correcte=false;
    if (p->resposta==p->taula[p->fila][p->columna])
    {
        correcte=true;
        p->taula_respostes[p->fila][p->columna]= p->resposta+ '0';

    }
    return correcte;
}
