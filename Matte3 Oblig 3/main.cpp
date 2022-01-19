#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>

using namespace std;

struct Vertex {
    float x;
    float y;
    float z;

    float r;
    float g;
    float b;
};

float myFunction(float x, float y) // Both Del 1 and Del 2
{
    float z = 0.0f;
    //same fuction as in task 2.3.6 in the math pdf from Dag
    z = 3 * x - pow(x, 3) - 3 * x * pow(y, 2);
    return z;
}

float function21(float x, float y)
{
    float z = 0.0f;
    //same fuction as in task 2.3.6 in the math pdf from Dag
    z = x*x*y*y - 2*x*y*y +y*y-1;
    return z;
}

vector <Vertex> createVertexVector()
{
    vector <Vertex> mVertices;
    float xmin = 0.0f, xmax = 2.0f, ymin = -1.0f, h = 0.5f;
    for (auto x = xmin; x < xmax; x += h)
    {
        float ymax{ 3.f};
        for (auto y = ymin; y < ymax; y += h)
        {
            float z = myFunction(x, y);
            mVertices.push_back(Vertex{ x, y, z, x, y, z });
            z = myFunction(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
            z = myFunction(x, y + h);
            mVertices.push_back(Vertex{ x, y + h, z, x, y, z });
            mVertices.push_back(Vertex{ x, y + h, z, x, y, z });
            z = myFunction(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
            z = myFunction(x + h, y);
            mVertices.push_back(Vertex{ x + h, y, z, x, y, z });
        }
    }
    return mVertices;
}

vector <Vertex> readFile()
{
    fstream myFile;
    vector <Vertex> mVertices;
    myFile.open("Vertexs.txt", ios::in);
    if (myFile.is_open())
    {
        myFile.ignore('\n');
        string line;
        while(getline(myFile,line)) 
        {
            float i[6];
            char dum[7];
            myFile >> dum[0] >> i[0] >> dum[1] >> i[1] >> dum[2] >> i[2] >> dum[3] >> i[3] >> dum[4] >> i[4] >> dum[5] >> i[5] >> dum[6];
            mVertices.push_back(Vertex{ i[0], i[1], i[2], i[3], i[4], i[5] });
        }
        myFile.close();
    }
    else cout << "Error: 01 File not open E" << endl;
    return mVertices;
}

void writeFile(vector <Vertex> mVerticesWrite)
{
    fstream myFile;
    myFile.open("Vertexs.txt", ios::out);
    if (myFile.is_open())
    {
        myFile << "Number of Vertices: " << mVerticesWrite.size() << '\n';
        for (auto i : mVerticesWrite)
        {
            myFile << '(' << i.x << ',' << i.y << ',' << i.z << '|' << i.r << ',' << i.g << ',' << i.b << ')' << '\n';
        }

        myFile.close();
    }
    else cout << "Error: 02 File not open E" << endl;
}

float numericIntegration(float function(float, float), float n)
{
    float volume{ 0.0f }, xmin{ 0.f }, xmax{ 2 }, ymin{ -1 }, hx{ (xmax - xmin) / n } , ymax {3.f}, hy = { (ymax - ymin) / n };
   
    for (auto x = xmin; x < xmax; x += hx)
    {
        for (auto y = ymin; y < ymax; y += hy)
        {
            float heigt = function(x, y);

            float particalVolume = heigt * hy * hx;
            volume += particalVolume;
        }
    }

    return volume;
}



int main()
{
    // Del 1
    vector <Vertex> mVerticesRead = readFile();
    vector <Vertex> mVerticesWrite = createVertexVector();
    writeFile(mVerticesWrite);

    // Del 2
    cout << numericIntegration(myFunction,5000) << endl;
    cout << numericIntegration(myFunction,10000) << endl;
}