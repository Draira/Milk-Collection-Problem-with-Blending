#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <chrono>

using namespace std;
/*
 * ----------------------------------------
 * 		Se definen las estructuras
 * ----------------------------------------
 */
struct Camion{
	string nombre;
	int capacidad;
	
	vector <int> rutaActual;
	vector <int> ID_rutaActual;
	vector <string> calidad_rutaActual;
	vector <int> cantidad_rutaActual;
	
	int feRutaActual;
	int totalCant_rutaActual;
	string calidadLeche; //Calidad final de la leche
	
	vector <int> mejorRuta;
	int feMejorRuta = 0;
	
}camion1, camion2, camion3;

struct Planta{
	vector <int> cantReqLeche; //cantidad de leche requerida por cada calidad de leche	
	vector <double> calidadLeche; //calidad que le asigna la planta a cada tipo de leche, va de mayor a menor A,B,C
	
}planta;

struct Granjas{
	vector <int> idNodo; 
	vector <int> coodX;
	vector <int> coodY;
	vector <string> calidadLG;
	vector <int> cantidadesLG;
	
	vector <int> posicionA;
	vector <int> posicionB;
	vector <int> posicionC;
	
	vector <int> cantidadesA;
	vector <int> cantidadesB;
	vector <int> cantidadesC;
	
	int totalLecheA;
	int totalLecheB;
	int totalLecheC;
	
}granjas;

//Aca almacenaremos los camiones
vector <Camion> cam;

//MEJOR SOLUCION
vector <int> feBestSol;
vector <int> rutaBestSol0;
vector <int> rutaBestSol1;
vector <int> rutaBestSol2;
/*-------------------------------------------------------------------------
 * 
 *		FUNCIONES
 * 
 *--------------------------------------------------------------------------  
 */
 
//Funciones
void read(string file);

bool capacidadRuta(Camion camion, vector <int> ruta);
bool cuotaPlanta(vector <int> ruta);
bool esFactible(Camion camion, vector <int> ruta);

//Funciones camiones
int sumarCantidad(vector <int> posicion);
int calidadTotalRuta(vector <int> ruta);

//Funciones granjas
vector <int> contarPosicion(string letra);

void movimiento1(Camion &c1, Camion &c2, int reqPlanta);
vector <vector<int>> movimiento2(vector <int> v2);
vector <vector<int>> movimiento3(vector <int> v3);
bool movimientoDoble(Camion &c1, Camion &c2, string letra);
bool existeEnRuta(vector <string> ruta, string letra);
bool movimientoTriple();

//int star_restart();
//void solInit(int asigCamion);
int solInit();

vector <int> idRuta(vector <int> ruta);
vector <int> coodXRuta(vector <int> ruta);
vector <int> coodYRuta(vector <int> ruta);
int calcularDistanciaTotal(vector <int> ruta);
int fEvaluacion(vector <int> vecino);

int generarVecindario(Camion &camion, vector <int> &ruta, int contador = 0);

vector <int> cantidadesRuta(vector <int> ruta);
vector <string> calidadesRuta(vector <int> ruta);

int calcularResto(vector <int> ruta, string letra);



/*-------------------------------------------------------------------------
 * 
 *		MAIN
 * 
 *--------------------------------------------------------------------------  
 */

int main(int argc, char** argv) {
	auto start = chrono::system_clock::now();
	read(argv[1]);
	//Veces que haremos re-star
	for(int i = 0; i < 10; ++i){
		
		
		cam.clear();
		int sol = solInit();
		
		if(sol == 1){
			return 0;
		}
		else{
			int c1 = 0, c2 = 0, c3 = 0;
			//Veces que iteraremos
			for(int j = 0; j < 40; ++j){
				if(c1 < 10){
					c1 = generarVecindario(cam[0], cam[0].rutaActual, c1);
					
				
				}
				if(c2 < 10){
					c2 = generarVecindario(cam[1], cam[1].rutaActual, c2);
					
					
				}
				if(c3 < 10){
					c3 = generarVecindario(cam[2], cam[2].rutaActual, c2);

				}
				if(c1+c2+c3  >= 30){
					break;
					/*
					bool esTipre = movimientoTriple();
					
					
					if(!esTipre){
						int randomMov = rand() % 3;
						
						if(randomMov == 0){
							bool esDoble = movimientoDoble(cam[0], cam[1], "A");
							
							if(esDoble){
								c1 = 0;
								c2 = 0;
								c3 = 0;
							}
							
						}
						if(randomMov == 1){
							bool esDoble = movimientoDoble(cam[0], cam[2], "A");
							if(esDoble){
								
								c1 = 0;
								c2 = 0;
								c3 = 0;
							}
						}
						if(randomMov == 2){
							bool esDoble = movimientoDoble(cam[1], cam[2], "B");
							if(esDoble){
								c1 = 0;
								c2 = 0;
								c3 = 0;
							}
						}
					}
					else{
						c1 = 0;
						c2 = 0;
						c3 = 0;
					}
					*/
				}
			}
		
			
			
			if(cam[0].feMejorRuta < cam[0].feRutaActual){
				cam[0].feMejorRuta = cam[0].feRutaActual;
				cam[0].mejorRuta = cam[0].rutaActual;
				feBestSol.push_back(cam[0].feMejorRuta);
				rutaBestSol0 =cam[0].mejorRuta;
			}
			
			if(cam[1].feMejorRuta  < cam[1].feRutaActual){
				cam[1].feMejorRuta = cam[1].feRutaActual;
				cam[1].mejorRuta = cam[1].rutaActual;
				feBestSol.push_back(cam[1].feMejorRuta);
				rutaBestSol1=cam[1].mejorRuta;
			}
			
			if(cam[2].feMejorRuta < cam[2].feRutaActual){
				cam[2].feMejorRuta = cam[2].feRutaActual;
				cam[2].mejorRuta = cam[2].rutaActual;
				feBestSol.push_back(cam[2].feMejorRuta);
				rutaBestSol2 =cam[2].mejorRuta;
			}
		
			if(feBestSol[0] < cam[0].feRutaActual){
				feBestSol.erase(feBestSol.begin() + 0);
				feBestSol.insert(feBestSol.begin() + 0, cam[0].feMejorRuta);
				
				rutaBestSol0 = cam[0].mejorRuta;	
			}
			
			if(feBestSol[1] < cam[1].feRutaActual){
				feBestSol.erase(feBestSol.begin() + 1);
				feBestSol.insert(feBestSol.begin() + 1, cam[1].feMejorRuta);
				
				rutaBestSol1 = cam[1].mejorRuta;
			}
			
			if(feBestSol[2] < cam[2].feRutaActual){
				feBestSol.erase(feBestSol.begin() + 2);
				feBestSol.insert(feBestSol.begin() + 2, cam[2].feMejorRuta);
				
				rutaBestSol2 = cam[2].mejorRuta;	
			}

		}
		
	}
	
	cout << "\n\n" << feBestSol[0] << " " << feBestSol[1] << " " << feBestSol[2] << "\n\n";
	
	vector <int> id0 = idRuta(rutaBestSol0);
	vector <int> id1 = idRuta(rutaBestSol1);
	vector <int> id2 = idRuta(rutaBestSol2);
	

	for(size_t i= 0; i < id0.size(); i++){
		cout << id0[i] <<";";
	}
	cout << " "<< calcularDistanciaTotal (rutaBestSol0) << " " << sumarCantidad(rutaBestSol0) <<" A\n";
	for(size_t i= 0; i < id1.size(); i++){
		cout << id1[i] <<";";
	}
	cout << " "<< calcularDistanciaTotal (rutaBestSol1) << " " << sumarCantidad(rutaBestSol1) <<" B\n";
	for(size_t i= 0; i < id2.size(); i++){
		cout << id2[i] <<";";
	}
	cout << " "<< calcularDistanciaTotal (rutaBestSol2) << " " << sumarCantidad(rutaBestSol2) <<" C\n\n";
	
	
	auto end = chrono::system_clock::now();
	auto elapsed = end - start;
	cout << elapsed.count()<< " milisegundos";
	return 0;
	
	
}


/*-------------------------------------------------------------------------
 * 
 *		FUNCIONES
 * 
 *--------------------------------------------------------------------------  
 */
 

//Funcion que lee y almacena los datos del archivo en las estructuras creadas
void read(string file){    
	
	//Abrir el txt
    ifstream archivo;
	archivo.open(file,ios::in);
	
	string texto;
	int i = 0;  //contador
	
    if (archivo.fail()) {
        cout << "No se pudo abrir el archivo";
        exit(1);
    }

    while (getline(archivo, texto)) {
        i++;
        
        //Toma las capacidades del camion y los almacena en su respectivo camion
        if(i == 2){
			string cami1;
			string cami2;
			string cami3;
            stringstream ss(texto);
            ss >> cami1 >> cami2 >> cami3;
            camion1.capacidad = stoi(cami1);
            camion2.capacidad = stoi(cami2);
            camion3.capacidad = stoi(cami3);
		}
		
		//Requerimientos de leche de cada planta
		if(i == 5){
			string cap1;
			string cap2;
			string cap3;
            stringstream ss(texto);
            ss >> cap1 >> cap2 >> cap3;
            
            planta.cantReqLeche.push_back(stoi(cap1));
            planta.cantReqLeche.push_back(stoi(cap2));
            planta.cantReqLeche.push_back(stoi(cap3));
		}
		
		if(i == 6){
			string cal1;
			string cal2;
			string cal3;
            stringstream ss(texto);
            ss >> cal1 >> cal2 >> cal3;
            planta.calidadLeche.push_back(atof(cal1.c_str()));  
            planta.calidadLeche.push_back(atof(cal2.c_str()));  
            planta.calidadLeche.push_back(atof(cal3.c_str()));
		}

		//almacena cada columna de la informacion de los grafos en vectores
        if(i> 8){
			//string total;
			string node;
			string ejeX;
			string ejeY;
			string tipoLeche;
			string cantLeche;
			
			stringstream ss(texto);
			
			ss >> /*total >> */ node >> ejeX >> ejeY >> tipoLeche >> cantLeche;
			
			//granjas.totalGranja = stoi(total);
			granjas.idNodo.push_back(stoi(node));
			granjas.coodX.push_back(stoi(ejeX));
			granjas.coodY.push_back(stoi(ejeY));
			granjas.calidadLG.push_back(tipoLeche);
			granjas.cantidadesLG.push_back(stoi(cantLeche));
		}
    }
    archivo.close();
}

//Funcion que calcula el resto real que sobra de todas las granjas que producen leche de un mismo tipo
int calcularResto(vector <int> ruta, string letra){
	int j;
	if(letra == "A"){
		j = 0;
	}
	if(letra == "B"){
		j = 1;
	}
	if(letra == "C"){
		j = 2;
	}
	//restoA = granjas.totalLecheA - planta.cantReqLeche[0];
	//Retorna la cantidades que de lache que hacen las granjas del tipo A
	vector <int> cantidad = cantidadesRuta(ruta); //me genera un vector con las posiciones
	//Lo ordenas con sort
	sort(cantidad.begin() , cantidad.end());
	
	int suma = 0;
	
	//Recorremos el sort
	for(size_t i=0; i < cantidad.size() ; ++i){
		suma = suma + cantidad[i];
		if(suma > planta.cantReqLeche[j]){
			break;
		}
	}
	return suma;
}

//Verifica de antemano si es problema puede llegar a tener solucion, solo a partir de premisas
int tieneSolucion(){
	
	int elemento = 0;
	
	int restoA = 0;
	int restoAB = 0;
	
	granjas.posicionA = contarPosicion("A");
    granjas.posicionB = contarPosicion("B");  
    granjas.posicionC = contarPosicion("C");
	    
	granjas.totalLecheA = sumarCantidad(granjas.posicionA);
    granjas.totalLecheB = sumarCantidad(granjas.posicionB);
    granjas.totalLecheC = sumarCantidad(granjas.posicionC);

    /*
    *-------------------------------------------------------------------------------------
	* Tomo todo lo anterior para que el problema tenga los requisitos mínimos de funcionar
	*-------------------------------------------------------------------------------------
	*/
	
    //Una vez tengo las leches totales debo verifica si cumple con lo de la planta;
    if(granjas.totalLecheA < planta.cantReqLeche[0]){
		cout <<"El problema no tiene solucion, porque toda la cantidad de leche A de las granjas no alcanzan a cumplir la cuota de la planta \n";
		elemento += 1;
	}
	else{
		//Calcular resto real
		restoA = calcularResto(granjas.posicionA, "A");
	}
	if((restoA + granjas.totalLecheB) < planta.cantReqLeche[1]){
		cout <<"El problema no tiene solucion, porque toda la cantidad de leche B de las granjas no alcanzan a cumplir la cuota de la planta \n";
		elemento += 1;
	}
	else{
		int restoB = calcularResto(granjas.posicionB, "B");
		restoAB = restoA + restoB;
	}
	if((restoAB + granjas.totalLecheC) < planta.cantReqLeche[2]){
		cout <<"El problema no tiene solucion, porque toda la cantidad de leche C de las granjas no alcanzan a cumplir la cuota de la planta \n";
		elemento += 1;
	}
	
	//Tambien debo verificar las capacidades de los camiones y de la cantidad de leche que producen las granjas 
	int sumaLecheTotal;
	int sumaCapacidadTotal;
	
	sumaLecheTotal = granjas.totalLecheA + granjas.totalLecheB + granjas.totalLecheC;
	sumaCapacidadTotal = camion1.capacidad + camion2.capacidad + camion3.capacidad;
	
	if(sumaLecheTotal > sumaCapacidadTotal){
		cout <<"El problema no tiene solucion, porque los camiones no tienen la capacidad suficiente para llevar toda la leche de las granjas \n";
		elemento += 1;
	}
   
	vector <int> sobras;
	vector <Camion> cami;
	
	cami.push_back(camion1);
	cami.push_back(camion2);
	cami.push_back(camion3);
	
	vector <int> total;
	
	total.push_back(granjas.totalLecheA);
	total.push_back(granjas.totalLecheB);
	total.push_back(granjas.totalLecheC);
	
    for(size_t i = 0; i < planta.cantReqLeche.size(); ++i){
		size_t contadorStrike = 0;
		vector <int> restas;
		vector <int> position;
		
		for(size_t j = 0; j < cami.size() ; ++j){
			
			if(planta.cantReqLeche[i] > cami[j].capacidad){
				contadorStrike += 1;
			}
			else{
				restas.push_back(cami[j].capacidad - planta.cantReqLeche[i]);
				position.push_back(j);
				
				if(total[i] > planta.cantReqLeche[i] && total[i] > cami[j].capacidad){
					sobras.push_back(granjas.totalLecheA - planta.cantReqLeche[i]);
				}
				else{
					sobras.push_back(0);
				}
			}
		}
		if(contadorStrike == cami.size()){
			cout << "\n El problema no tiene solucion, porque el camion no tiene la capacidad para llevar lo que pide la planta \n";
			elemento += 1;
			break;
		}
		int minElementIndex = min_element(restas.begin(),restas.end()) - restas.begin();
		cami.erase(cami.begin() + minElementIndex);
		
		if(i != 2){
			total[i+1] += sobras[minElementIndex];
			sobras.erase(sobras.begin() + minElementIndex);
		}
		else{
			if(total[i] > cami[minElementIndex].capacidad){
				cout <<"\n El problema no tiene solucion porque no hay forma de cumplir los requerimientos de las plantas \n";
				elemento+=1;
			}
		}
	}
	return elemento;
}

//Crea una solucion inicial factible
int solInit(){
			
	int haySolucion = tieneSolucion();
	
	if(haySolucion == 0){

		//------------------------------------------------------------
		//Esta parte del código escoje una combinacion random de 123
		//------------------------------------------------------------
		int contador = 0;
		string cadena = "123";
		int random = rand()%6; //ramdom que escogera una de las 6 combinaciones
		int asigCamion;
			
		do{
			if(random == contador){
				break;
			}
			contador++;
		}while(next_permutation(cadena.begin(), cadena.end()));
		
		asigCamion = stoi(cadena);
		int primero, segundo, tercero;
		
		tercero = asigCamion%10;
		asigCamion = asigCamion/10;
		segundo = asigCamion%10;
		primero = asigCamion/10;

		/*-------------------------------------------------------------------------------------
		* Luego segun mi random asigno un camion a la calidad de leche en este orde ABC
		* Ejemplo:
		*			A		B		C
		*		camion1	 camion3  camion2
		*
		*Nos beneficia tratar la leche en ese orden, y para que los camiones sigan el orden 
		*de la leche se crea un vector Camiones para mantener ese orden
		*-------------------------------------------------------------------------------------
		*/
		 
		if(primero == 1){
			
			camion1.nombre = "camion 1";
			camion1.rutaActual = granjas.posicionA;
			
			camion1.ID_rutaActual = idRuta(camion1.rutaActual);
			camion1.calidad_rutaActual = calidadesRuta(camion1.rutaActual);
			camion1.cantidad_rutaActual = cantidadesRuta(camion1.rutaActual);
			
			camion1.calidadLeche = "A";
			camion1.totalCant_rutaActual = granjas.totalLecheA;
			camion1.feRutaActual = fEvaluacion(camion1.rutaActual);
			cam.push_back(camion1);
			
			
		}
		
		if(primero == 2){

			camion2.nombre = "camion 2";
			camion2.rutaActual = granjas.posicionA;
			
			camion2.ID_rutaActual = idRuta(camion2.rutaActual);
			camion2.calidad_rutaActual = calidadesRuta(camion2.rutaActual);
			camion2.cantidad_rutaActual = cantidadesRuta(camion2.rutaActual);
			
			camion2.calidadLeche = "A";
			camion2.totalCant_rutaActual = granjas.totalLecheA;
			camion2.feRutaActual = fEvaluacion(camion2.rutaActual);
			cam.push_back(camion2);
		
		}
		
		if(primero == 3){
			
			camion3.nombre = "camion 3";
			camion3.rutaActual = granjas.posicionA;
			
			camion3.ID_rutaActual = idRuta(camion3.rutaActual);
			camion3.calidad_rutaActual = calidadesRuta(camion3.rutaActual);
			camion3.cantidad_rutaActual = cantidadesRuta(camion3.rutaActual);
			
			camion3.calidadLeche = "A";
			camion3.totalCant_rutaActual = granjas.totalLecheA;
			camion3.feRutaActual = fEvaluacion(camion3.rutaActual);
			cam.push_back(camion3);
			
		}
		
		if(segundo == 1){
			
			camion1.nombre = "camion 1";
			camion1.rutaActual = granjas.posicionB;
			
			camion1.ID_rutaActual = idRuta(camion1.rutaActual);
			camion1.calidad_rutaActual = calidadesRuta(camion1.rutaActual);
			camion1.cantidad_rutaActual = cantidadesRuta(camion1.rutaActual);
			
			camion1.calidadLeche = "B";
			camion1.totalCant_rutaActual = granjas.totalLecheB;
			camion1.feRutaActual = fEvaluacion(camion1.rutaActual);
			cam.push_back(camion1);
			
		}
		
		if(segundo == 2){
			
			camion2.nombre = "camion 2";
			camion2.rutaActual = granjas.posicionB;
			
			camion2.ID_rutaActual = idRuta(camion2.rutaActual);
			camion2.calidad_rutaActual = calidadesRuta(camion2.rutaActual);
			camion2.cantidad_rutaActual = cantidadesRuta(camion2.rutaActual);
			
			camion2.calidadLeche = "B";
			camion2.totalCant_rutaActual = granjas.totalLecheB;
			camion2.feRutaActual = fEvaluacion(camion2.rutaActual);
			cam.push_back(camion2);
			
		}
		
		if(segundo == 3){
			
			camion3.nombre = "camion 3";
			camion3.rutaActual = granjas.posicionB;
			
			camion3.ID_rutaActual = idRuta(camion3.rutaActual);
			camion3.calidad_rutaActual = calidadesRuta(camion3.rutaActual);
			camion3.cantidad_rutaActual = cantidadesRuta(camion3.rutaActual);
			
			camion3.calidadLeche = "B";
			camion3.totalCant_rutaActual = granjas.totalLecheB;
			camion3.feRutaActual = fEvaluacion(camion3.rutaActual);
			cam.push_back(camion3);
		
		}
		
		if(tercero == 1){

			camion1.nombre = "camion 1";
			camion1.rutaActual = granjas.posicionC;
			
			camion1.ID_rutaActual = idRuta(camion1.rutaActual);
			camion1.calidad_rutaActual = calidadesRuta(camion1.rutaActual);
			camion1.cantidad_rutaActual = cantidadesRuta(camion1.rutaActual);
			
			camion1.calidadLeche = "C";
			camion1.totalCant_rutaActual = granjas.totalLecheC;
			camion1.feRutaActual = fEvaluacion(camion1.rutaActual);
			cam.push_back(camion1);
			
		}
		
		if(tercero == 2){
			
			camion2.nombre = "camion 2";
			camion2.rutaActual = granjas.posicionC;
			
			camion2.ID_rutaActual = idRuta(camion2.rutaActual);
			camion2.calidad_rutaActual = calidadesRuta(camion2.rutaActual);
			camion2.cantidad_rutaActual = cantidadesRuta(camion2.rutaActual);
			
			camion2.calidadLeche = "C";
			camion2.totalCant_rutaActual = granjas.totalLecheC;
			camion2.feRutaActual = fEvaluacion(camion2.rutaActual);
			cam.push_back(camion2);
		
		}
		
		if(tercero == 3){

			camion3.nombre = "camion 3";
			camion3.rutaActual = granjas.posicionC;
			
			camion3.ID_rutaActual = idRuta(camion3.rutaActual);
			camion3.calidad_rutaActual = calidadesRuta(camion3.rutaActual);
			camion3.cantidad_rutaActual = cantidadesRuta(camion3.rutaActual);
			
			camion3.calidadLeche = "C";
			camion3.totalCant_rutaActual = granjas.totalLecheC;
			camion3.feRutaActual = fEvaluacion(camion3.rutaActual);
			cam.push_back(camion3);
		
		}
/*------------------------------------------------------------------------------------
* Una vez asignado el orden vemos si es capaz de ser una solucion factible,
* es decir verificando que esa calidad que lleva el camion no sobrepase su capacidad
*-------------------------------------------------------------------------------------
*/
		int cont = 0;
		while(!capacidadRuta(cam[0], cam[0].rutaActual)){//Comprobamos si el camion tiene capacidad para almacenar la leche A, 
			
			if(cont < 50){
				cont += 1;
				movimiento1(cam[0], cam[1], 0);
			}
			else{
				cont = 0;
				cam.clear();
				solInit(); 					   		
				break;
				return 0;
			}										 
		}
		
		while(!capacidadRuta(cam[1], cam[1].rutaActual)){ //Comprobamos si el camion tiene capacidad para almacenar la leche de B, o la leche de B mas el sobrante de A											  
			
			if(cont < 50){
				cont += 1;
				movimiento1(cam[1], cam[2], 1); 				  //si sobra lo almacenamos en el camion que contiene la leche C
			}
			else{
				cont = 0;
				cam.clear();
				solInit(); 					   		
				break;
				return 0;
			}	
			
		}
		
		if(!capacidadRuta(cam[2], cam[2].rutaActual)){ //Finalmente verificamos si la cantidad de la leche C de las granjas 
				
			cam.clear();							   //Mas los remanentes de la leche A y B anteriores
			solInit();							   //son capaces de ser almacenados en el camion, sino es asi no hay solucion
			return 0;
		}
		
/*----------------------------------------------------------------------------------------------------------------------------------
* Una vez asignado comprobado que no se inflinje las capacidades de los camiones,
* verificaremos que la calidad que lleva cada uno supere la cuota pedida por la planta
*------------------------------------------------------------------------------------------------------------------------------------
*/ 
		if(!(cuotaPlanta(cam[0].rutaActual))){		//Si todo lo que hay en el camion que contiene la leche A no supera la cuota de la planta
			
			cam.clear();							//entonces no hay solucion
			solInit();
			return 0;
		} 
		
		while(!cuotaPlanta(cam[1].rutaActual)){ //La leche B no supera la cuota de la planta
	
			int sobraA = calcularResto(cam[0].rutaActual, "A");   //¿Cuanto sobra de A para pasarle a B?
			int faltaB = planta.cantReqLeche[1] - cam[1].totalCant_rutaActual;  //¿Cuanto es lo que falta de B para cumplir su cuota con la planta?
			int espacioSobraB = cam[1].capacidad - cam[1].totalCant_rutaActual; //¿Cuanto espacio le sobra al camion B para añadir mas leche?
			
			if(espacioSobraB >= faltaB){ //entonces puedo sacar un poco del camion que contiene la leche A, solo si a este le sobra
				if(sobraA >= faltaB){
					
					if(cont < 50){
						cont += 1;
						movimiento1(cam[0], cam[1], 0); 				  //si sobra lo almacenamos en el camion que contiene la leche C
					}
					else{
						cont = 0;
						cam.clear();
						solInit(); 					   		
						break;
						return 0;
					}	
				}
				else{ //Si no puede suplir tal cantidad...
					cam.clear();
					solInit();
					break;
					return 0;
				}
			}
			else{ //...y si el camion que contiene la leche B no puede almacenar lo que le falta, entonces no hay solucion
				cam.clear();
				solInit();
				break;
				return 0;
			}
		}
		
		while(!cuotaPlanta(cam[2].rutaActual)){ //La leche C no supera la cuota de la planta
			
			int sobraA = calcularResto(cam[0].rutaActual, "A");   //¿Cuanto sobra de A para pasarle a C?
			int sobraB = calcularResto(cam[1].rutaActual, "B");  //¿Cuanto sobra de B para pasarle a C?
			int faltaC = planta.cantReqLeche[2] - cam[2].totalCant_rutaActual; //¿Cuanto es lo que falta de B para cumplir su cuota con la planta?
			int espacioSobraC = cam[2].capacidad - cam[2].totalCant_rutaActual; //¿Cuanto espacio le sobra al camion B para añadir mas leche?
			
			if(espacioSobraC >= faltaC){
				if((sobraA + sobraB) >= faltaC){
					if(sobraB >= faltaC){//puedo sacar un poco del camion que contiene la leche B... 
						if(cont < 50){
							cont += 1;
							movimiento1(cam[1], cam[2], 1); 				  //si sobra lo almacenamos en el camion que contiene la leche C
						}
						else{
							cont = 0;
							cam.clear();
							solInit(); 					   		
							break;
							return 0;
						}
						
					}
					if(sobraA >= faltaC){//...o del camion que lleva la leche A, solo si a estos les sobra
						if(cont < 50){
							cont += 1;
							movimiento1(cam[0], cam[2], 0);				  //si sobra lo almacenamos en el camion que contiene la leche C
						}
						else{
							cont = 0;
							cam.clear();
							solInit(); 					   		
							break;
							return 0;
						}
					}
				}
				else{ 
					cam.clear();
					solInit();
					break;
					return 0;
				}
			}
			else{//Si no puede suplir tal cantidad, y si el camion que contiene la leche B no puede almacenar lo que le falta, no hay solucion
				cam.clear();
				solInit();
				break;
				return 0;
			}
		}
	}
	else{
		cout <<"El problema no tiene solucion";
		return 1;
	}
	
	
	
	
	return 0;
}



//Funcion que retorna una ruta aleatoria para las granjas que producen leche del mismo tipo
vector <int> contarPosicion(string letra){
	
	vector <int> posicion;
	vector <string> vect = granjas.calidadLG; 
	int tamanoVect = granjas.calidadLG.size();
	
	for(int i = 0; i < tamanoVect ; i++){
		if(letra == vect[i]){
			posicion.push_back(i);
		}
	}
	return posicion;
}

//Funcion que retorna los ID de la ruta tomada
vector <int> idRuta(vector <int> ruta){
	
	vector <int> id;
	
	for(size_t i = 0; i < ruta.size(); i++){
		id.push_back(granjas.idNodo[ruta[i]]);
	}
	
	//Ahora a la ruta de ID le añado el ID de la planta al inicio y al final para demarcar que comienza y termina alli su ruta
	int InicioFinal = granjas.idNodo[0];
	id.insert(id.begin(), InicioFinal);
	id.insert(id.begin() + id.size(), InicioFinal);
	
	return id;
}

//Funcion que retorna las coordenadas del eje X de la ruta tomada 
vector <int> coodXRuta(vector <int> ruta){
	
	vector <int> coodRutaX;
	
	for(size_t i = 0; i < ruta.size(); i++){
		coodRutaX.push_back(granjas.coodX[ruta[i]]);
	}
	
	return coodRutaX;
}

//Funcion que retorna las coordenadas del eje Y de la ruta tomada
vector <int> coodYRuta(vector <int> ruta){
	
	vector <int> coodRutaY;
	
	for(size_t i = 0; i < ruta.size(); i++){
		coodRutaY.push_back(granjas.coodY[ruta[i]]);
	}
	
	return coodRutaY;
}

//Funcion que retorna las calidades de la leche recolectada en cada granja de la ruta tomada
vector <string> calidadesRuta(vector <int> ruta){
	
	vector <string> calRuta;
	
	for(size_t i = 0; i < ruta.size(); i++){
		calRuta.push_back(granjas.calidadLG[ruta[i]]);
	}
	
	return calRuta;
}

//Funcion que retorna las cantidades de la leche recolectada en cada granja de la ruta tomada
vector <int> cantidadesRuta(vector <int> ruta){
	
	vector <int> canRuta;
	
	for(size_t i = 0; i < ruta.size(); i++){
		canRuta.push_back(granjas.cantidadesLG[ruta[i]]);
	}
	
	return canRuta;
}




//Funcion que suma el total de litros de leche recolectados de de todas las granjas de la ruta
int sumarCantidad(vector <int> posicion){
	
	int tamanoPosicion = posicion.size();
	vector <int> calidad = granjas.cantidadesLG;
	
	
	int suma = 0;
	for(int i = 0; i < tamanoPosicion; i++){
		suma += calidad[posicion[i]];
	}
	return suma;
}

//Toma la ruta del camion y calcula que tipo de calidad es si es C retorna 2, si es B retorna 1, si es A retorna 0
int calidadTotalRuta(vector <int> ruta){
	
	vector <int> posicion = ruta;
	int tamanoPosicion = ruta.size();
	vector <string> calidad = granjas.calidadLG;
	vector <string> letras;
	
	for(int i = 0; i < tamanoPosicion; i++){
		letras.push_back(calidad[posicion[i]]);
	}
	
	if(count(letras.begin(), letras.end(), "C")){
		return 2;
	}
	else{
		if(count(letras.begin(), letras.end(), "B")){
			return 1;
		}
		else{
			return 0;
		}
	}
}




//retorna true si la capacidad del camion es mayor a la cantidad de leche que lleva y false en caso contrario
bool capacidadRuta(Camion camion , vector <int> ruta){
	
	int cantidadLeche = sumarCantidad(ruta);
	if (camion.capacidad >= cantidadLeche){
		
		return true;
	}
	else{
		
		return false;
	}
}

//Suma toda la leche que lleva el camion y lo compara con el requerimiento de la planta
bool cuotaPlanta(vector <int> ruta){
	
	int totalLecheRuta;
	int tipoLeche;
	
	totalLecheRuta = sumarCantidad(ruta);
	
	tipoLeche = calidadTotalRuta(ruta);
	
	
	if(totalLecheRuta >= planta.cantReqLeche[tipoLeche]){
		
		return true;
	}
	else{
		
		return false;
	}
}

//Verifica simultaneamente la capacidad del camion y la cuota de la leche de la planta
bool esFactible(Camion camion, vector <int> ruta){
	if(capacidadRuta(camion, ruta) && cuotaPlanta(ruta) ){
		return true;
	}
	else{
		return false;
	}
}

//Sacar una granja de la ruta de un camion y se la pasa a otra;
void movimiento1(Camion &c1, Camion &c2, int reqPlanta){
	int indice1 = rand() % c1.rutaActual.size();
	int indice2 = rand() % c2.rutaActual.size();
	int aux;
	
	//Haces un vector copiando la ruta donde realmente lo mueves y compruebas si pasa la planta
	vector <int> copiaRuta1 = c1.rutaActual;
	vector <int> copiaRuta2 = c2.rutaActual;
	//Le saco este mono y veo si cumple la cuota de la planta
	aux = copiaRuta1[indice1];
	
	copiaRuta1.erase(copiaRuta1.begin() + indice1);
	copiaRuta2.insert(copiaRuta2.begin() + indice2, aux);
	
	
	
	if((planta.cantReqLeche[reqPlanta] <= sumarCantidad(copiaRuta1)) && (c2.capacidad >= sumarCantidad(copiaRuta2))) {
		
		c1.rutaActual = copiaRuta1;
		c2.rutaActual = copiaRuta2;
		
		c1.ID_rutaActual = idRuta(c1.rutaActual);
		c1.calidad_rutaActual = calidadesRuta(c1.rutaActual);
		c1.cantidad_rutaActual = cantidadesRuta(c1.rutaActual);
		c1.totalCant_rutaActual = sumarCantidad(c1.rutaActual);
		c1.feRutaActual = fEvaluacion(c1.rutaActual);
		
		c2.ID_rutaActual = idRuta(c2.rutaActual);
		c2.calidad_rutaActual = calidadesRuta(c2.rutaActual);
		c2.cantidad_rutaActual = cantidadesRuta(c2.rutaActual);
		c2.totalCant_rutaActual = sumarCantidad(c2.rutaActual);
		c2.feRutaActual = fEvaluacion(c2.rutaActual);
	}
}

//Mueve una granja al azar en diferentes posiciones de la ruta
vector <vector <int>>  movimiento2(vector <int> v2){
	
	vector <int> generadorV = v2;
	
	int movimientos = generadorV.size() -1;
	int k = rand() % generadorV.size();

	vector <vector <int>> vecindario;
	//vector <vector <int>> fevaluacion;
	
	int i = 0;
	for(int j = 0; j < movimientos; ++j){
		if(k+i != movimientos){//mientras k+i no sea el ultimo nodo de la lista
			int aux = generadorV[k + i];
			generadorV[k + i] = generadorV[k + i + 1];
			generadorV[k + i + 1] = aux;
			vecindario.push_back(generadorV);
		}
		else{
			int aux2 = generadorV[movimientos];
			generadorV.pop_back();
			generadorV.insert(generadorV.begin(), aux2);
			vecindario.push_back(generadorV);
			k = 0;
			i = -1;
		}
		++i;
	}
	return vecindario;
}

//Intercambia dos granjas dentro de la misma ruta
vector <vector <int>> movimiento3(vector <int> v3){
	
	vector <int> generadorV = v3;
	vector <vector <int>> vecindario;
	
	int movimientos = generadorV.size() -1;
	int num = rand() % generadorV.size();
	
	for(int i=0; i < movimientos; ++i){
		if(num != i){
			iter_swap(generadorV.begin() + num, generadorV.begin() + i);
			vecindario.push_back(generadorV);
			iter_swap(generadorV.begin() + num, generadorV.begin() + i);
		}
	}
	return vecindario;
}



int calcularDistanciaTotal(vector <int> ruta){
	
	vector <int> vecX, vecY;
	vecX = coodXRuta(ruta);
	vecY = coodYRuta(ruta);
	
	int plantaX, plantaY;
	plantaX = granjas.coodX[0];
	plantaY = granjas.coodY[0];
		
	vecX.insert(vecX.begin(), plantaX);
	vecX.insert(vecX.begin() + vecX.size(), plantaX);
	
	vecY.insert(vecY.begin(), plantaY);
	vecY.insert(vecY.begin() + vecY.size(), plantaY);
	
	int sumaDis = 0;
	
	for(size_t i = 0; i < vecX.size() -1 ; ++i){
		int x1 = vecX[i];
		int x2 = vecX[i+1];
		int y1 = vecY[i];
		int y2 = vecY[i+1];
		int distancia = sqrt(pow((x2-x1),2)+ pow((y2-y1),2));

		sumaDis = sumaDis + distancia;
	}
	return sumaDis;
}

int fEvaluacion(vector <int> vecino){
	//Mi funcion de evaluacion debería ser calidad por cantidad - distancia recorrida
	int calTipoLeche = calidadTotalRuta(vecino); //devuelve un entero 0=A, 1=B 2=C

	double calTipoPlanta = planta.calidadLeche[calTipoLeche]; //Segun lo anterior me devuelve el % del valor del tipo de leche ej: B = 0.7
	
	int suma = sumarCantidad(vecino); //Sumo toda mi cantidad de la leche
	
	int distancia = calcularDistanciaTotal(vecino);
	int fe = calTipoPlanta * suma - distancia;

	return fe;
}

int generarVecindario(Camion &camion, vector <int> &ruta, int contador){

	if(contador < 10){
		
		vector <vector <int>> vecindario;
		vector <int> feVecindario;
		
		int randomMovi = rand() % 2;
		if(randomMovi == 0){
			vecindario = movimiento2(ruta);
		}
		else{
			vecindario = movimiento3(ruta);
		}
		
		for(size_t k = 0; k < vecindario.size(); k++){ //Recorro el vecindario
			feVecindario.push_back(fEvaluacion(vecindario[k])); //Y agrego cafa fe del vecindario en una lista
		}
		
		
		//Tomo el elemento máximo del vector de la fe del vecindario
		int maxElementIndex = max_element(feVecindario.begin(),feVecindario.end()) - feVecindario.begin();
		int maxElement = *max_element(feVecindario.begin(),feVecindario.end());
		
		if(maxElement > camion.feRutaActual){ 
			
			camion.rutaActual = vecindario[maxElementIndex];
			camion.feRutaActual = fEvaluacion (vecindario[maxElementIndex]);
			
			camion.calidad_rutaActual = calidadesRuta(camion.rutaActual);
			camion.cantidad_rutaActual = cantidadesRuta(camion.rutaActual);
			camion.totalCant_rutaActual = sumarCantidad(camion.rutaActual);
			
			contador = 0;
			return contador;
		}
		
		else{
			//Aca es donde debo buscar de nuevo, porque ya maximo no habia
			
			contador += 1;
			//generarVecindario(camion, ruta, contador);
		}
	}
	else{
		
		return contador;
	}
	//En caso de que no haya pasado por nada que retorne 100
	return contador;
}



bool existeEnRuta(vector <string> ruta, string letra){
	return find(ruta.begin(), ruta.end(), letra) != ruta.end();
}

bool movimientoTriple(){
	
	//Caso para A: vamos a buscar una A en B y en C. PARA B Y C SOLOS ESTO SE ROMPE
	bool existeEnB = existeEnRuta(cam[1].calidad_rutaActual, "A");
	bool existeEnC = existeEnRuta(cam[2].calidad_rutaActual, "A");
	
	if(existeEnB && existeEnC){
		int contador = 1;
		//Movimiento triple
		
		while(contador > 0){
			//Tomo uno de A de A
			int randomA = rand() % cam[0].rutaActual.size();
			vector <int> CopiaRutaA = cam[0].rutaActual;
			int auxA = CopiaRutaA[randomA];
			CopiaRutaA.erase(CopiaRutaA.begin() + randomA);
			
			//Tomo uno de A de B 
			vector <int> postAinB;
			for(size_t i = 0; i < cam[1].rutaActual.size(); i++){
				if(calidadesRuta(cam[1].rutaActual)[i] == "A"){ 
					postAinB.push_back(i);
				}
			}
			
			int randomB = rand() % postAinB.size();
			vector <int> CopiaRutaB = cam[1].rutaActual;
			int auxB = CopiaRutaB[postAinB[randomB]];
			CopiaRutaB.erase(CopiaRutaB.begin() + postAinB[randomB]);
			
			//Tomo un A de C
			vector <int> postAinC;
			for(size_t i = 0; i < cam[2].rutaActual.size(); i++){
				if(calidadesRuta(cam[2].rutaActual)[i] == "A"){
					postAinC.push_back(i);
				}
			}
			
			int randomC = rand() % postAinC.size();
			vector <int> CopiaRutaC = cam[2].rutaActual;
			int auxC = CopiaRutaC[postAinC[randomC]];
			CopiaRutaC.erase(CopiaRutaC.begin() + postAinC[randomC]);
			
			//Veo la suma de lo que queda sin los 3 restoA, restoB, restoC
			//Luego a A le sumo el A de C, a B el A de A y a C el A de B
			//Inserto
			
			CopiaRutaA.insert(CopiaRutaA.begin() + randomA, auxC);
			CopiaRutaB.insert(CopiaRutaB.begin() + postAinB[randomB], auxA);
			CopiaRutaC.insert(CopiaRutaC.begin() + postAinC[randomC], auxB);
	
			//Si cumplen la cuota pasan, sino busco otro que no cumpliera
			//ME FALTO COMPROBAR SI NO SUPERO LA CAPACIDAD DEL CAMION AAAAHHH
			
			if(esFactible(cam[0], CopiaRutaA) && esFactible(cam[1], CopiaRutaB) && esFactible(cam[2], CopiaRutaC)){
				//El cambio se hace definitivo
				
				if(cam[0].feMejorRuta + cam[1].feMejorRuta + cam[2].feMejorRuta < cam[0].feRutaActual + cam[1].feRutaActual + cam[2].feRutaActual ){
					cam[0].feMejorRuta = cam[0].feRutaActual;
					cam[1].feMejorRuta = cam[1].feRutaActual;
					cam[2].feMejorRuta = cam[2].feRutaActual;
					
					cam[0].mejorRuta = cam[0].rutaActual;
					cam[1].mejorRuta = cam[1].rutaActual;
					cam[2].mejorRuta = cam[2].rutaActual;
				}
				
				cam[0].rutaActual = CopiaRutaA;
				cam[1].rutaActual = CopiaRutaB;
				cam[2].rutaActual = CopiaRutaC;
				
				cam[0].ID_rutaActual = idRuta(cam[0].rutaActual);
				cam[0].calidad_rutaActual = calidadesRuta(cam[0].rutaActual);
				cam[0].cantidad_rutaActual = cantidadesRuta(cam[0].rutaActual);
				cam[0].totalCant_rutaActual = sumarCantidad(cam[0].rutaActual);
				cam[0].feRutaActual = fEvaluacion(cam[0].rutaActual);
				
				cam[1].ID_rutaActual = idRuta(cam[1].rutaActual);
				cam[1].calidad_rutaActual = calidadesRuta(cam[1].rutaActual);
				cam[1].cantidad_rutaActual = cantidadesRuta(cam[1].rutaActual);
				cam[1].totalCant_rutaActual = sumarCantidad(cam[1].rutaActual);
				cam[1].feRutaActual = fEvaluacion(cam[1].rutaActual);
				
				cam[2].ID_rutaActual = idRuta(cam[2].rutaActual);
				cam[2].calidad_rutaActual = calidadesRuta(cam[2].rutaActual);
				cam[2].cantidad_rutaActual = cantidadesRuta(cam[2].rutaActual);
				cam[2].totalCant_rutaActual = sumarCantidad(cam[2].rutaActual);
				cam[2].feRutaActual = fEvaluacion(cam[2].rutaActual);
				
				contador = 0;
				
				return true;
			}
			else{
				if(contador == 20){
					//No se haya ningun cambio
					
					return false;
				}
				else{
					contador += 1;
				}
			}
		}
	}
	else{
		
		return false;
	}
	
	return false;
}

bool movimientoDoble(Camion &c1, Camion &c2, string letra){
	
	cout <<"Movimiento doble";
	bool existeEnC1 = existeEnRuta(c1.calidad_rutaActual, letra);
	bool existeEnC2 = existeEnRuta(c2.calidad_rutaActual, letra);
	
	int contador = 1;
	
	if(existeEnC1 && existeEnC2){
		
		while(contador > 0){
			
			
			//Tomo una cantidad de la leche "letra" del camion 1
			int random1 = rand() % c1.rutaActual.size();
			vector <int> CopiaRuta1 = c1.rutaActual;
			int aux1 = CopiaRuta1[random1];
			
			
			
			
			
			CopiaRuta1.erase(CopiaRuta1.begin() + random1);
			
			//Tomo una cantidad de la leche "letra" del camion 2
			vector <int> letraIn2;
			for(size_t i = 0; i < c2.rutaActual.size(); i++){
				if(calidadesRuta(c2.rutaActual)[i] == letra){ 
					letraIn2.push_back(i);
				}
			}
			
			int random2 = rand() % letraIn2.size();
			vector <int> CopiaRuta2 = c2.rutaActual;
			int aux2 = CopiaRuta2[letraIn2[random2]];
			
			

			
			CopiaRuta2.erase(CopiaRuta2.begin() + letraIn2[random2]);
			
			
			
			
			
			CopiaRuta1.insert(CopiaRuta1.begin() + random1, aux2);
			CopiaRuta2.insert(CopiaRuta2.begin() + letraIn2[random2], aux1);
			
			
			
			
			
			
			if(esFactible(c1, CopiaRuta1) && esFactible(c2, CopiaRuta2)){
				
				cout <<"\nEs factible\n";
				if(c1.feMejorRuta + c2.feMejorRuta < c1.feRutaActual + c2.feRutaActual){
					c1.feMejorRuta = c1.feRutaActual;
					c2.feMejorRuta = c2.feRutaActual;
					
					c1.mejorRuta = c1.rutaActual;
					c2.mejorRuta = c2.rutaActual;
				}
				
				
				c1.rutaActual = CopiaRuta1;
				c2.rutaActual = CopiaRuta2;
				
				c1.ID_rutaActual = idRuta(c1.rutaActual);
				c1.calidad_rutaActual = calidadesRuta(c1.rutaActual);
				c1.cantidad_rutaActual = cantidadesRuta(c1.rutaActual);
				c1.totalCant_rutaActual = sumarCantidad(c1.rutaActual);
				c1.feRutaActual = fEvaluacion(c1.rutaActual);
				
				c2.ID_rutaActual = idRuta(c2.rutaActual);
				c2.calidad_rutaActual = calidadesRuta(c2.rutaActual);
				c2.cantidad_rutaActual = cantidadesRuta(c2.rutaActual);
				c2.totalCant_rutaActual = sumarCantidad(c2.rutaActual);
				c2.feRutaActual = fEvaluacion(c2.rutaActual);
				
				contador = 0;
				return true;
			}
			else{
				
				if(contador == 20){
					
					return false;
					
				}
				else{
					contador += 1;
				}
			}
		}
	}
	else{
		
		return false;
	}
	return false;
}
