#include <iostream>
#include <cmath>
#include <iomanip>  
#include <fstream>
#include <vector>


using namespace std; 

int coun = 0;

int NumOfSignDig = 4;
long double eps = pow(10, -NumOfSignDig -1);

void DrawTable(int n) {
    ofstream out("ans.txt", ios_base::app);
    string t;
    int flag = 1;
    ifstream in("tmptable.txt");
    in >> t;
    out << t<<endl<<"|";

    for (int i = 0; i < n; i++) {
        in >> t;
        out << setprecision(10) << setw(15) << t << "|";
    }
    out << "\n"<<"+";
    for (int i = 0; i < n; i++)
        out << "---------------+";
    out << "\n";
    while (flag) {
        for (int i=0; i < n; i++) {
            in >> t;
            if (t == "/0") {
                flag = 0; break;
            }

            out << "|" << setprecision(10) << setw(15) << t;
        }
        if (flag )out << "|\n";
        else out << "\n";
    }
    flag = 1;
    while (flag) {
        in >> t;
        if (t == "/0") {
            flag = 0; break;
        }
        out << setprecision(3) << t<<" ";
    }
    out << "\n\n";
    flag = 1;
    while (flag) {
        in >> t;
        if (t == "/0") {
            flag = 0; break;
        }
        out << setprecision(4) << t << " ";
    }
    out << "\n\n";
    
    in.close();
    out.close();
    ofstream out2("tmptable.txt");
    out2.close();
}



long double Func(long double x){
    ++coun;
    return exp(7*x)+exp(-6*x)+6*x*x+12*x+7-x*x*x; 

 }

void PassiveSearch2(){//метод пассивного поиска
    long double m = Func(-1);
	long double ind = -1e7;
    for(long double i = -100000;i<0;i++){
        long double j= i/100000;
	    if(m>Func(j)){
		    ind = j;
		    m=Func(j);
			
		}
    }
    cout<< "PassiveSearch2:\n " <<"Minimum at the point: "<< setprecision(10) <<ind <<" value: "<< setprecision(10) << " " << m<<endl;
}

void PassiveSearch(long double a, long double b) {//метод пассивного поиска
    ofstream out("tmptable.txt", ios_base::app);
    
    out << "Passive_Search" << "\n"  << " " << "i" << " " << "x" << " " << "y"  << endl;
    
    vector<long double> x;
    vector<long double> fx;
    int k = 10000;
    //int count = 0;

    for(int i = 0; i < k + 1; i++) {
        x.push_back(a + ((b - a) * i) / k);
        fx.push_back(Func(x[i]));
        out <<" "<< i <<" " << x[i]<<" " << fx[i]<<"\n";
        
    }
    out << " /0 ";
    int min_i = -1;
    long double min_v = 1e10;
    for (int i = 0; i < fx.size(); i++) {
        if (min_v > fx[i]) {
            min_v = fx[i];
            min_i = i;
        }
    }
    min_v = floor(min_v * 1000) / 1000;
    out<< "Minimum at the point: " << setprecision(5) << x[min_i] << " value: " << setprecision(5) << " " << min_v<< " /0 ";
    
   
    
    out << "Func was called " << coun << " times /0 \n"; 
    coun = 0;
    out.close();
    DrawTable(3);

    
}

void Dichotomy(long double a,long double b,int n) {
    ofstream out("tmptable.txt", ios_base::app);
    if (n == 0) {
        out << "Dichotomy " << "\n" <<" n"<< " " << "a(n)" << " " << "b(n)" << " " << "c(n)" << " " << "F(c(n))" << " " << "d(n)" << " " << "F(d(n))" << endl;
    }
    long double eps = pow(10, -NumOfSignDig -1);
    long double delta = eps/2 ;
    long double d = (a + b) / 2 + delta;
    long double c = (a + b) / 2 - delta;

    //out  <<" "<< n <<" "<< setprecision(6)  << a << " " << setprecision(7)  << b << " " << setprecision(7)<<c<< " " << setprecision(7) << d<<endl;
    if ((b - a) / 2 < eps){
        long double x = Func((a + b) / 2);
        x = floor(x * 1000) / 1000;

        out<<" /0 "<< "Minimum at the point: " << setprecision(5) << floor(((a + b) / 2) * 10000) / 10000 << " value: " << setprecision(5) << x <<" /0 ";
        out << "Func was called " << coun << " times /0 \n";
        coun = 0;
        out.close();
        DrawTable(7);
    }
    else {
       
        long double delta = eps / 2;
        long double fc = Func(c);
        long double fd = Func(d);
        out << " " << n << " " << setprecision(10) << a << " " << setprecision(10) << b << " " << setprecision(10) << c << " " << setprecision(10) << fc << " " << setprecision(10) << d << " " << setprecision(10) << fd << endl;
        out.close();
        if (fc <= fd)

            Dichotomy(a, d, n + 1);
        else
            Dichotomy(c, b, n + 1);

    }
    
}

void ZolotoeSechenie() {
    ofstream out("tmptable.txt");
    out << "ZolotoeSechenie " << "\n" << " n" << " " << "a(n)" << " " << "b(n)" << " " << "c(n)" << " " << "F(c(n))" << " " << "d(n)" << " " << "F(d(n))" << endl;
    long double a = -1.;
    long double b = 0.;
    long double d = (sqrt(5) - 1) * (b - a) / 2 + a;
    long double c = (3 - sqrt(5)) * (b - a) / 2 + a;
    long double fc = Func(c);
    long double fd = Func(d);
    int n = 0;

    while ((b - a) / 2 >= eps) {
        
        if(fc <= fd){
            b = d;
            d = c;
            fd = fc;
            c = (3 - sqrt(5)) * (b - a) / 2 + a;
            fc = Func(c);
            
        }
        else{
            a = c;
            c = d;
            fc = fd;
            d = (sqrt(5) - 1) * (b - a) / 2 + a;
            fd= Func(d);
        }
        out << " " << n << " " << setprecision(10) << a << " " << setprecision(10) << b << " " << setprecision(10) << c << " " << setprecision(10) << fc << " " << setprecision(10) << d << " " << setprecision(10) << fd << endl;
        n++;
    }
    long double x = Func((a + b) / 2);
    x = floor(x * 1000) / 1000;
    out << " /0 " << "Minimum at the point: " << setprecision(5) << floor(((a + b) / 2) * 10000) / 10000 << " value: " << setprecision(5) << x << " /0 ";
    out << "Func was called " << coun << " times /0 \n";
    coun = 0;
    out.close();
    DrawTable(7);

}

void Fib() {
    int n = 23;
    int i = 1;
    vector<int> F;
    F.push_back(0);
    F.push_back(1);
    for (int j = 0; j < n+4; j++) {
        F.push_back(F[j] + F[j + 1]);
    }

    ofstream out("tmptable.txt");
    out << "Fib" << "\n" << " n" << " " << "a(n)" << " " << "b(n)" << " " << "c(n)" << " " << "F(c(n))" << " " << "d(n)" << " " << "F(d(n))" << endl;
    long double a = -1.;
    long double b = 0.;
    long double d = a + (b - a) * F[n + 1] / F[n+2];
    long double c = a + (b - a) * F[n] / F[n + 2];
    long double fc = Func(c);
    long double fd = Func(d);
    

    while (i < n) {
        
        if (fc < fd) {
            b = d;
            d = c;
            fd = fc;
            i++;
            c = a + (b - a) * F[n + 1 - i] / F[n - i + 3];
            fc = Func(c);
        }
        else {
            a = c;
            c = d;
            fc = fd;
            i++;
            d = a + (b - a) * F[n + 2 - i] / F[n -i + 3];
            fd = Func(d);
        }
        out << " " << i - 2 << " " << setprecision(10) << a << " " << setprecision(10) << b << " " << setprecision(10) << c << " " << setprecision(10) << fc << " " << setprecision(10) << d << " " << setprecision(10) << fd << endl;
        
    }
    long double  y= Func((a + b) / 2);
    y = floor(y * 1000) / 1000;
    long double x = floor(((a + b) / 2) * 10000) / 10000;
    out << " /0 " << "Minimum at the point: " << setprecision(5) << x << " value: " << setprecision(5) << y << " /0 ";
    out << "Func was called " << coun << " times /0 \n";
    coun = 0;
    out.close();
    DrawTable(7);

}

void clear_out() {
    ofstream out("ans.txt");
    out.close();
    return;
}

long double DFunc(long double x) {
    ++coun;
    return 7*exp(7 * x) - 6 * exp(-6 * x) + 12 * x + 12  - 3 * x * x;

}

long double D2Func(long double x) {
    ++coun;
    return 49 * exp(7 * x) + 36 * exp(-6 * x) + 12 - 6 * x;

}

void Tangent() {
    ofstream out("tmptable.txt");
    out << "Tangent" << "\n" << " n" << " " << "a(n)" << " " << "dF(a(n))" << " " << "F(a(n))" << " " << "b(n)" << " " << "dF(b(n))" << " " << "F(b(n))" << " " << "c(n)" << " " << "dF(c(n))"  << endl;
    long double a = -1.;
    long double b = 0.;
    int i = 1;
    long double c = -1 ;
    long double da = DFunc(a);
    long double db = DFunc(b);
    long double fa = Func(a);
    long double fb = Func(b);
    c = (a * da - b * db - fa + fb) / (da - db);
    long double dc = DFunc(c);
    while (abs(b - a) > eps && abs(dc) > eps && abs(fa - fb) > eps) {
        out << " " << i << " " << setprecision(10) << a << " " << setprecision(8) << da << " " << setprecision(10) << fa << " " << setprecision(10) << b << " " << setprecision(10) << db << " " << setprecision(10) << fb << " "  << setprecision(10) << c << " " << setprecision(9) << dc << endl;
        if (dc > 0) {
            b = c;
            i++;
            db = dc;
            fb = Func(b);
            c = (a * da - b * db - fa + fb) / (da - db);
            dc = DFunc(c);
        }
        else {
            a = c;
            i++;
            da = dc;
            fa = Func(a);
            c = (a * da - b * db - fa + fb) / (da - db);
            dc = DFunc(c);
        }
        
    }
    out << " " << i << " " << setprecision(10) << a << " " << setprecision(8) << da << " " << setprecision(10) << fa << " " << setprecision(10) << b << " " << setprecision(10) << db << " " << setprecision(10) << fb << " " << setprecision(10) << c << " " << setprecision(9) << dc << endl;
    long double x = c;
    x = long double(int(x * 10000)) / 10000;
    long double y = floor((Func(x) * 1000)) / 1000;
    out << " /0 " << "Minimum at the point: " << setprecision(5) << x << " value: " << setprecision(5) << y << " /0 ";
    out << "Func was called " << coun << " times /0 \n";
    coun = 0;
    out.close();
    DrawTable(9);

}

void NethonRavson() {
    ofstream out("tmptable.txt");
    long double x = -1.0;
    long double dfx = DFunc(x);
    long double d2fx;
    int i = 1;
    out << "NethonRavson" << "\n" << " n" << " " << "x(n)" << " " << "Dx(n)" << " " <<"D2x(n)" <<  endl;
    while (abs(dfx)>eps/100){
        d2fx = D2Func(x); 
        out << " " << i << " " << setprecision(10) << x << " " << setprecision(8) << dfx << " " << setprecision(9) << d2fx << endl;
        x -= dfx/d2fx;
        i++;
        dfx = DFunc(x);
    }
    d2fx = D2Func(x);
    out << " " << i << " " << setprecision(10) << x << " " << setprecision(8) << dfx << " " << setprecision(9) << d2fx << endl;

    x = long double(round(x * 10000)) / 10000;
    long double y = floor((Func(x) * 1000)) / 1000;
    out << " /0 " << "Minimum at the point: " << setprecision(5) << x << " value: " << setprecision(5) << y << " /0 ";
    out << "Func was called " << coun << " times /0 \n";
    coun = 0;
    out.close();
    DrawTable(4);
}

void Sek() {
    ofstream out("tmptable.txt");
    long double x = -1.0;
    long double x_prew = 0.0;
    long double dfx = DFunc(x);
    long double dfx_prew = DFunc(x_prew);
    
    long double d2fx;
    int i = 1;
    out << "Sek" << "\n" << " n" << " " << "x(n)" << " " << "x(n-1)" << " " << "Dx(n)" << " " << "Dx(n-1)" << " " << "D2x(n)" << endl;
    while (abs(dfx) > eps) {
        d2fx = (dfx-dfx_prew)/(x-x_prew);
        out << " " << i << " " << setprecision(10) << x << " " << setprecision(10) << x_prew << " " << setprecision(8) << dfx << " " << setprecision(10) << dfx_prew << " " << setprecision(9) << d2fx << endl;
        x_prew = x;
        dfx_prew = dfx;
        x -= dfx / d2fx;
        i++;
        dfx = DFunc(x);
    }
    d2fx = (dfx - dfx_prew) / (x - x_prew);
    out << " " << i << " " << setprecision(10) << x << " " << setprecision(10) << x_prew << " " << setprecision(8) << dfx << " " << setprecision(10) << dfx_prew << " " << setprecision(9) << d2fx << endl;

    x = long double(round(x * 10000)) / 10000;
    long double y = floor((Func(x) * 1000)) / 1000;
    out << " /0 " << "Minimum at the point: " << setprecision(5) << x << " value: " << setprecision(5) << y << " /0 ";
    out << "Func was called " << coun << " times /0 \n";
    coun = 0;
    out.close();
    DrawTable(6);

}

int main(){
    
    bool run = 1;
    int mcase;
    while (run) {
        cout << "1-PassiveSearch\n";
        cout << "2 - Dichotomy\n";
        cout << "3 - ZolotoeSechenie\n";
        cout << "4 - Fib\n";
        cout << "5 -  Tangent\n";
        cout << "6 -  NethonRavson\n";
        cout << "7 -  Sek\n";
        cout << "9 - Clear out\n";
        //cout << "3 - PassiveSearchV2Control(7)\n";

        cout << "0 - exit\n";
        cin >> mcase;
        switch (mcase) {
        case 0:
            
            run = 0;
            break;
        case 1:
            PassiveSearch(-1.0,0.0);
            break;
        case 2:
            Dichotomy(-1.0,0.0,0);
            break;
        case 3:
            ZolotoeSechenie();
            break;
        case 4:
            Fib();
            break;
        case 5:
            Tangent();
            break;
        case 6:
            NethonRavson();
            break;
        case 7:
            Sek();
            break;
       /* case 3:
            PassiveSearch2();
            break;*/
        case 9:
            clear_out();
            break;
        default:
            cout << "no methods\n";
            break;
        }
    }
    ofstream out("tmptable.txt");
    out.close();
    return 0;
    
}
