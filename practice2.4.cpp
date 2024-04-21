#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>

using namespace std;

long long int mod(long long int g, long long x, long long p, long long y);
long long nod(long long p, long long g);
bool prost(long long x);

bool prost(long long x) //�������� �� ��������
{
    if (x < 2)
    {
        return false;
    }
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}
long long nod(long long p, long long g) //�������� �� ��������� ��������
{
    while (p > 0 && g > 0)
        if (p > g)
            p %= g;
        else
            g %= p;
    return p + g;
}
long long int mod(long long int g, long long x, long long p, long long y) // g^x mod p 
{
    long long  res = 1;
    if (g % p == 0)
    {
        return 0;
    }

    x = x % y;

    if (x % y == 0)
    {
        return 1;
    }
    else
    {
        for (int i = 1; i <= x; i++)
        {
            res = (res * g) % p;
        }
    }
    return res;
}
int main() {
    system("chcp 65001");
    long long p, g, xa,xb;
    long int Ya,Yb, r, e, m;
    srand(time(0));
    p = 1 + rand() % 100000000;
    g = 1 + rand() % (p - 1);
    while (!prost(p) || !prost(g) || nod(p, g) != 1) 
    {
        p = 1 + rand() % 100000000;
        g = 1 + rand() % (p - 1);
    }
    cout << "G = "<< g << " " <<"P = " << p << endl;
    cout << "Введите ключ A: ";
    cin >> xa;
    cout << "Введите ключ B: ";
    cin >> xb;

    Ya = mod(g, xa, p, p - 1); // вычисление открытого ключа
    cout << "Открытый ключ A: " << Ya << endl;

    Yb = mod(g, xb, p, p - 1); // вычисление открытого ключа
    cout << "Открытый ключ B: " << Yb << endl;

    string M;
    cout << "Введите сообщение (английские букы или цифры): ";
    getline(cin, M);
    getline(cin, M);

    vector<int> shif;
    vector<int> deshif;

    for (int i = 0; i < M.length(); i++)
    {
        shif.push_back((int)M[i]);
    }

    long long K;
    for (int i = 2; i < p - 1; i++) 
    {
        if (nod(i, p - 1) == 1)
        {
            K = i;
            break;
        }
    }
    r = mod(g, K, p, p - 1);
    cout << "r = " << r << endl;
    for (int i = 0; i < shif.size(); i++) // шифрование
    { 
        e = ((shif[i] % p) * (mod(Yb, K, p, p - 1))) % p; 
        deshif.push_back(e); 
    }
    cout << "e = " << e << endl;

    for (int i = 0; i < deshif.size(); i++) //дешифрование
    { 
        m = ((deshif[i] % p) * mod(r, (p - 1 - xb), p, p - 1)) % p;
        cout << (char)m;
    }
}

