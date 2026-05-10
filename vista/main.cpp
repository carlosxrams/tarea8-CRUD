#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Estudiante.h"
using namespace std;
int main(){
    string codigo, nombres, apellidos, direccion, fecha_nacimiento;
    int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;
    bool codigoValido = false;
    regex formatoCodigo("E[0-9]{3}");
    bool nombreValido = false;
    bool apellidoValido = false;
    regex formatoNombre("^[a-zA-ZáéíóúÁÉÍÓÚñÑ ]+$");
    bool direccionValida = false;
    regex formatoDireccion("^[a-zA-Z0-9áéíóúÁÉÍÓÚñÑ ,.#-]+$");
    string inputTel;
    bool telValido = false;
    regex formatoTel("^[0-9]{8}$");
    string fecha_nac;
    bool fechaValida = false;
    regex formatoFecha("^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$");
    MYSQL_RES* resultado;
    int id_sangre;
    bool existe = false;
    int q_estado;
    

    //Ingreso de codigo

    do {
        cout << "Ingrese el codigo (Formato E001): ";
        cin >> codigo;

        
        if (codigo.length() == 4 && regex_match(codigo, formatoCodigo)) {
            codigoValido = true;
        }
        else {
            cout << " Formato incorrecto, use una 'E' seguida de 3 numeros" << endl;
        }
    } while (!codigoValido);
    cin.ignore();
    
    //Ingreso de nombres

    do {
        cout << "Ingrese nombres: ";
        getline(cin, nombres);

        
        if (!nombres.empty() && nombres.length() <= 60 && regex_match(nombres, formatoNombre)) {
            nombreValido = true;
        }
        else {
            cout << " El nombre solo debe contener letras, espacios y maximo 60 caracteres" << endl;
        }
    } while (!nombreValido);
    
    
    //Ingreso de apellidos

    do {
        cout << "Ingrese apellidos: ";
        getline(cin, apellidos);

     
        if (!apellidos.empty() && apellidos.length() <= 60 && regex_match(apellidos, formatoNombre)) {
            apellidoValido = true;
        }
        else {
            cout << " Los apellidos solo deben contener letras, espacios y maximo 60 caracteres" << endl;
        }
    } while (!apellidoValido);

    //Ingreso de direccion

    do {
        cout << "Ingrese la direccion: ";
        getline(cin, direccion);

        
        if (!direccion.empty() && direccion.length() <= 100 && regex_match(direccion, formatoDireccion)) {
            direccionValida = true;
        }
        else {
            cout << " Direccion invalida, no puede hacer uso de comillas o simbolos especiales extraños (max 100 caracteres)" << endl;
        }
    } while (!direccionValida);

    //Ingreso de telefono 

    do {
        cout << "Ingrese numero de telefono: ";
        cin >> inputTel;

        
        if (regex_match(inputTel, formatoTel)) {
            
            telefono = stoi(inputTel);
            telValido = true;
        }
        else {
            cout << " Numero de telefono invalido, el telefono debe contener exactamente 8 digitos numericos, no se permiten letras, espacios ni simbolos" << endl;
            
        }
    } while (!telValido);
    cin.ignore();

    //fechanacimiento

    do {
        cout << "Ingrese fecha de nacimiento (AAAA-MM-DD): ";
        cin >> fecha_nacimiento;

        if (regex_match(fecha_nacimiento, formatoFecha)) {
            
            int anio = stoi(fecha_nacimiento.substr(0, 4));
            int mes = stoi(fecha_nacimiento.substr(5, 2));
            int dia = stoi(fecha_nacimiento.substr(8, 2));

            
            time_t t = time(0);
            tm* now = localtime(&t);
            int anioActual = now->tm_year + 1900;
            int mesActual = now->tm_mon + 1;
            int diaActual = now->tm_mday;

            
            if (anio > anioActual || (anio == anioActual && mes > mesActual) ||
                (anio == anioActual && mes == mesActual && dia > diaActual)) {
                cout << " La fecha no puede ser futura." << endl;
            }
           
            else {
                bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
                int diasPorMes[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
                if (esBisiesto) diasPorMes[2] = 29;

                if (dia <= diasPorMes[mes]) {
                    fechaValida = true;
                }
                else {
                    cout << " Error, el mes " << mes << " no tiene " << dia << " dias." << endl;
                }
            }
        }
        else {
            cout << " Use el formato AAAA-MM-DD (Ej: 2005-06-15)." << endl;
        }
    } while (!fechaValida);

    //VALIDACION TIPOS DE SANGRE
    ConexionBD cn;
    cn.abrir_conexion();
    //tipo de sangre

    do {
        cout << "Ingrese ID de tipo de sangre: ";
        if (!(cin >> id_sangre)) { 
            cout << " [!] Error: Ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore(1000, '\n');

        string consulta = "SELECT id_tipo_sangre FROM tipo_sangre WHERE id_tipo_sangre = " + to_string(id_sangre);
        const char* c = consulta.c_str();

        q_estado = mysql_query(cn.getConector(), c);

        if (!q_estado) {
            resultado = mysql_store_result(cn.getConector());

            if (resultado != NULL) {
                if (mysql_num_rows(resultado) > 0) {
                    existe = true;
                    cout << "  Tipo de sangre validado" << endl;
                }
                else {
                    cout << "  El ID " << id_sangre << " no existe en la tabla" << endl;
                }
                mysql_free_result(resultado);
            }
        }
        else {
            
            cout << "  Error de MySQL: " << mysql_error(cn.getConector()) << endl;
        }
    } while (!existe);

    id_tipo_sangre = id_sangre;

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

