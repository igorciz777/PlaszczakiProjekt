#include<iostream>
#define pkt pair<int, int>
using namespace std;

int iloczyn_wektorowy(pkt X, pkt Y, pkt Z)
{
	int x1 = Z.first - X.first, y1 = Z.second - X.second,
		x2 = Y.first - X.first, y2 = Y.second - X.second;
	return x1*y2 - x2*y1;
}
bool sprawdz(pkt X, pkt Y, pkt Z)
{
	return min(X.first, Y.first) <= Z.first && Z.first <= max(X.first, Y.first) 
		&& min(X.second, Y.second) <= Z.second && Z.second <= max(X.second, Y.second);
}

bool czy_przecinaja(pkt A, pkt B, pkt C, pkt D)
{
	int v1 = iloczyn_wektorowy(C, D, A),
		v2 = iloczyn_wektorowy(C, D, B),
		v3 = iloczyn_wektorowy(A, B, C),
		v4 = iloczyn_wektorowy(A, B, D);
	if((v1>0&&v2<0||v1<0&&v2>0)&&(v3>0&&v4<0||v3<0&&v4>0)) return 1;
	
	if(v1 == 0 && sprawdz(C, D, A)) return 1;
	if(v2 == 0 && sprawdz(C, D, B)) return 1;
	if(v3 == 0 && sprawdz(A, B, C)) return 1;
	if(v4 == 0 && sprawdz(A, B, D)) return 1;
	
	return 0;
}
int main()
{
	pair<int, int> A, B, C, D;
	
	cout<<"Podaj wspólrzedne punktu A: ";
	cin>>A.first>>A.second;
	
	cout<<"Podaj wspólrzedne punktu B: ";
	cin>>B.first>>B.second;
	
	cout<<"Podaj wspólrzedne punktu C: ";
	cin>>C.first>>C.second;
	
	cout<<"Podaj wspólrzedne punktu D: ";
	cin>>D.first>>D.second;

	if(czy_przecinaja(A, B, C, D)) 
		cout<<"Odcinki sie przecinaja\n";
	else
		cout<<"Odcinki sie nie przecinaja\n";

	
	return 0;
}