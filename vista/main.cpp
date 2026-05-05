#include <iostream>
#include "Estudiante.h"
using namespace std;
int main(){
    string codigo, nombres, apellidos, direccion, fecha_nacimiento;
    int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;
    cout << "Ingrese el codigo: ";
    cin >> codigo;
    cin.ignore();
    cout << "Ingrese nombres: ";
    getline(cin, nombres);
    cout << "Ingrese apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese la direccion: ";
    getline(cin, direccion);
    cout << "Ingrese el telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Ingrese fecha de nacimiento: ";
    getline(cin, fecha_nacimiento);
    cout << "Ingrese tipo de sangre: ";
    cin >> id_tipo_sangre;

    Estudiante e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, codigo, id_estudiante);
    e.crear();
    e.leer();


    //actualizacion
    cout << "Ingrese el ID a modificar: ";
    cin >> id_estudiante;
    cin.ignore();
    cout << "Ingrese el codigo: ";
    cin >> codigo;
    cin.ignore();
    cout << "Ingrese nombres: ";
    getline(cin, nombres);
    cout << "Ingrese apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese la direccion: ";
    getline(cin, direccion);
    cout << "Ingrese el telefono: ";
    cin >> telefono;
    cin.ignore();
    cout << "Ingrese fecha de nacimiento: ";
    getline(cin, fecha_nacimiento);
    cout << "Ingrese tipo de sangre: ";
    cin >> id_tipo_sangre;
     

    e.setId_estudiante(id_estudiante);
    e.setCodigo(codigo);
    e.setNombres(nombres);
    e.setApellidos(apellidos);
    e.setDireccion(direccion);
    e.setTelefono(telefono);
    e.setFecha_nacimiento(fecha_nacimiento);
    e.setId_tipo_sangre(id_tipo_sangre);


    e.actualizar();
    e.leer();
    cout << "Ingrese el ID a eliminar: ";
    cin >> id_estudiante;
    e.setId_estudiante(id_estudiante);
    e.borrar();
    e.leer();

    //Estudiante e = Estudiante();
    //e.leer();
    
}

