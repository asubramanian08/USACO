//everynode to everynode, O(N^3)
//look at starleague part 1 lesson 8

int main(void)
{
    int numPast;
    int **adjMatrix;

    for (int i = 0; i < numPast; i++)
        for (int j = 0; j < numPast; j++)
            for (int k = 0; k < numPast; k++)
                if (adjMatrix[j][k] > adjMatrix[j][i] + adjMatrix[i][k])
                    adjMatrix[j][k] = adjMatrix[j][i] + adjMatrix[i][k];
}