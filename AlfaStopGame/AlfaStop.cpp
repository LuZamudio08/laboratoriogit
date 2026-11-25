#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

//1. funciones de Alfa Stop.
//a. fucion(evalua) {si existe la palabra en el archivo de palabras} if(true){Registra la palabra en el historial} Else{Pedir repetir palabra}


int main(){
//interfas
cout<<"Bienvenido a Alfa Stop"<<endl;
cout<<"Seleccione una opción:"<<endl;
cout<<"1. Modo Alfabético"<<endl;
cout<<"2. Modo Aleatorio"<<endl;
cout<<"3. Mostrar resultados anteriores de partidas"<<endl;
cout<<"4. Indicaciones"<<endl;
cout<<"5. Creditos y salir"<<endl;
int opciones;
cin >> opciones;
switch(opciones){
    case 1: { // Modo Alfabético

        //1. iniciar cronómetro
        //2. vector de letras de la a-z

        for (char letra = 'a'; letra <= 'z'; ++letra) {
            string palabra;
            cout << "Letra: " << letra << endl;
            cin>> palabra;
            if(palabra[0] != letra){
                cout<<"La palabra no comienza con la letra "<<letra<<". Intenta de nuevo."<<endl;
                --letra; // Decrementar para repetir la misma letra
                continue;
            }
            else{
                while(true){
                    ifstream archivoPalabras("letra_" + string(1, letra) + ".txt");
                        string palabraArchivo;
                        bool palabraValida = false;

                        while (getline(archivoPalabras, palabraArchivo, ',')) {
                            if (palabra == palabraArchivo) {
                                palabraValida = true;
                                if (palabraValida) {
                                    cout << "La palabra '" << palabra << "' es válida." << endl;
                                    // Aquí puedes agregar la lógica para registrar la palabra en el historial
                                    ofstream historial("historial.txt", ios::app);
                                    historial << letra << ": " << palabra << endl;
                                    historial.close();
                                } else {
                                    cout << "La palabra '" << palabra << "' no es válida. Intenta de nuevo." << endl;
                                    cin >> palabra; // Pedir al usuario que ingrese otra palabra
                                }
                                break;
                            }
                        }
                    break; // Salir del bucle si la palabra es válida
                
            }
        }
        //5. cerrar cronómetro

        int time;
        cout<<"Tardaste "<<time<<" segundos."<<endl;
        cout<<"Promedio por palabra: "<<time/26<<" segundos."<<endl;

        break;
    }
    case 2: { // Modo Aleatorio
        //1. iniciar cronómetro
        //2. vector de letras de la a-z
        //3. ciclo de elección de letra y después pedir escribir la palabra (función a)
        //4. broke al completar las 26-27 letras
        //5. cerrar cronómetro
        //6. Cout tiempo y promedio por palabra

        int tiempo=0;
        cout<<"Tardaste "<<tiempo<<" segundos."<<endl;
        cout<<"Promedio por palabra: "<<tiempo/26<<" segundos."<<endl;

    }


        case 3:{
        // Mostrar resultados anteriores de partidas (Historial.txt)
        break;
        }
    case 4:{
        // Indicaciones
        // No cuentan palabras conjugadas
        break;
    }

    case 5:{
        // Creditos y salir
        ifstream creditos("Créditos.txt");
        string lineaCredito;
        while (getline(creditos, lineaCredito)) {
            cout << lineaCredito << endl;
        }
        creditos.close();

        break;

    }
return 0;
}