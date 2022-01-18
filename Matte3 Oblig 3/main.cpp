#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

struct Vertex {
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
};

float function(float x, float y)
{
    float z = 0.0f;
    //same fuction as in task 2.3.6 in the math pdf from Dag
    z = 3 * x - pow(x, 3) - 3 * x * pow(y, 2);
    return z;
}

vector <Vertex> createVertexVector()
{
    vector <Vertex> mVertices;
    float xmin = 0.0f, xmax = 1.0f, ymin = 0.0f, ymax = 0.1f, h = 0.5f;
    for (auto x = xmin; x < xmax; x += h)
    {
        for (auto y = ymin; y < ymax; y += h)
        {
            float z = function(x, y);
            mVertices.push_back(Vertex{ x, y, z, x, y, z });
            z = function(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
            z = function(x, y + h);
            mVertices.push_back(Vertex{ x, y + h, z, x, y, z });
            mVertices.push_back(Vertex{ x, y + h, z, x, y, z });
            z = function(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
            z = function(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
        }
    }
    return mVertices;
}

vector <Vertex> readFile()
{
    ifstream myFile;
    vector <Vertex> mVertices;
    myFile.open("Vertexs.txt");
    if (myFile.is_open())
    {
        myFile.ignore('\n');
        while(!myFile.eof())
        {
            float i[5];
            char dum[6];
            myFile >> dum[0] >> i[0] >> dum[1] >> i[1] >> dum[2] >> i[2] >> dum[3] >> i[3] >> dum[4] >> i[4] >> dum[5] >> i[5] >> dum[6];
            mVertices.push_back(Vertex{ i[0] ,i[1] , i[2] ,i[3] ,i[4] ,i[5] });
        }
        myFile.close();
    }
    else cout << "Error: 01 File not open E" << endl;
    return mVertices;
}

void writeFile(vector <Vertex> mVerticesWrite)
{
    ofstream myFile;
    myFile.open("Vertexs.txt");
    if (myFile.is_open())
    {
        myFile << "Number of Vertices :" << mVerticesWrite.size() << '\n';
        for (auto i : mVerticesWrite)
        {
            myFile << '(' << i.x << ',' << i.y << ',' << i.z << '|' << i.r << ',' << i.g << ',' << i.b << ')' << '\n';
        }

        myFile.close();
    }
    else cout << "Error: 02 File not open E" << endl;
}

int main()
{
    vector <Vertex> mVerticesRead = readFile();
    vector <Vertex> mVerticesWrite = createVertexVector();
    writeFile(mVerticesWrite);
}