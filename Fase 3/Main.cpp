#include <iostream>
#include <string>
#include <limits>
#include "biblioteca.h"

using namespace std;

int main() {
    BibliotecaDB db;

//db para cargar los daots
    db.cargarAutores();
    db.cargarLibros();
    db.cargarEstudiantes();
    db.cargarPrestamos();

    int opcionPrincipal;

    do {
        cout << "\n===== MENU BIBLIOTECA =====\n";
        cout << "1. Gestionar Autores\n";
        cout << "2. Gestionar Libros\n";
        cout << "3. Gestionar Estudiantes\n";
        cout << "4. Gestionar Prestamos\n";
        cout << "5. Guardar y Salir\n";
        cout << "Opcion: ";
        cin >> opcionPrincipal;
// validacion para las entradas
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida, escribe un numero.\n";
            continue;
        }

        switch (opcionPrincipal) {
// ================== AUTORES ==================
            case 1: {
                int opcionAutor;
                do {
                    cout << "\n--- MENU AUTORES ---\n";
                    cout << "1. Agregar Autor\n";
                    cout << "2. Listar Autores\n";
                    cout << "3. Actualizar Autor\n";
                    cout << "4. Eliminar Autor\n";
                    cout << "5. Volver al menu principal\n";
                    cout << "Opcion: ";
                    cin >> opcionAutor;

                    switch (opcionAutor) {
                        case 1: { //agregamos el autor
                            cin.ignore();
                            string nombre, nacionalidad;
                            cout << "Nombre del Autor: "; getline(cin, nombre);
                            cout << "Nacionalidad: "; getline(cin, nacionalidad);
                            db.agregarAutor(nombre, nacionalidad);
                            break;
                        }
                        case 2: db.listarAutores(); break; //imprimimos la listade autores
                        case 3: {  //actualizar los autores q estan
                            int id;
                            string nombre, nacionalidad;
                            cout << "ID del autor a actualizar: "; cin >> id; cin.ignore();
                            cout << "Nuevo nombre: "; getline(cin, nombre);
                            cout << "Nueva nacionalidad: "; getline(cin, nacionalidad);
                            db.actualizarAutor(id, nombre, nacionalidad);
                            break;
                        }
                        case 4: { // eliminar autores
                            int id;
                            cout << "ID del autor a eliminar: "; cin >> id;
                            db.eliminarAutor(id);
                            break;
                        }
                    }
                } while (opcionAutor != 5);
                break;
            }

// ================== LIBROS ==================
            case 2: {
                int opcionLibro;
                do {
                    cout << "\n--- MENU LIBROS ---\n";
                    cout << "1. Agregar Libro\n";
                    cout << "2. Listar Libros\n";
                    cout << "3. Actualizar Libro\n";
                    cout << "4. Eliminar Libro\n";
                    cout << "5. Volver al menu principal\n";
                    cout << "Opcion: ";
                    cin >> opcionLibro;

                    switch (opcionLibro) {
                        case 1: { //agregamos un libro, esto necesita un autor 
                            if (db.autores.empty()) {
                                cout << "Primero debes registrar autores.\n";
                                break;
                            }
                            cin.ignore();
                            string titulo, isbn;
                            int ano, id_autor;
                            cout << "Titulo: "; getline(cin, titulo);
                            cout << "ISBN: "; getline(cin, isbn);
                            cout << "Anio: "; cin >> ano;
                            cout << "\nAutores disponibles:\n";
                            db.listarAutores();
                            cout << "ID del Autor: "; cin >> id_autor;
                            db.agregarLibro(titulo, isbn, ano, id_autor);
                            break;
                        }
                        case 2: db.listarLibros(); break; // mostrar inventario
                        case 3: {//actualizar el libro
                            int id, ano;
                            cin.ignore();
                            string titulo, isbn;
                            cout << "ID del libro a actualizar: "; cin >> id; cin.ignore();
                            cout << "Nuevo titulo: "; getline(cin, titulo);
                            cout << "Nuevo ISBN: "; getline(cin, isbn);
                            cout << "Nuevo anio: "; cin >> ano;
                            db.actualizarLibro(id, titulo, isbn, ano);
                            break;
                        }
                        case 4: {//borrar libros
                            int id;
                            cout << "ID del libro a eliminar: "; cin >> id;
                            db.eliminarLibro(id);
                            break;
                        }
                    }
                } while (opcionLibro != 5);
                break;
            }

 // ================== ESTUDIANTES ==================
            case 3: 
                int opcionEst;
                do {
                    cout << "\n--- MENU ESTUDIANTES ---\n";
                    cout << "1. Agregar Estudiante\n";
                    cout << "2. Listar Estudiantes\n";
                    cout << "3. Actualizar Estudiante\n";
                    cout << "4. Eliminar Estudiante\n";
                    cout << "5. Volver al menu principal\n";
                    cout << "Opcion: ";
                    cin >> opcionEst;

                    switch (opcionEst) {
                        case 1: {{ // agregamos al estudiante
                            cin.ignore();
                            string nombre, grado;
                            cout << "Nombre del Estudiante: "; getline(cin, nombre);
                            cout << "Grado: "; getline(cin, grado);
                            db.agregarEstudiante(nombre, grado);
                            break;
                        }
                        case 2: db.listarEstudiantes(); break;//mostamos listra de estudianets
                        case 3: {//actualizamos el perfil del estudiante
                            int id;
                            string nombre, grado;
                            cout << "ID del estudiante a actualizar: "; cin >> id; cin.ignore();
                            cout << "Nuevo nombre: "; getline(cin, nombre);
                            cout << "Nuevo grado: "; getline(cin, grado);
                            db.actualizarEstudiante(id, nombre, grado);
                            break;
                        }
                        case 4: {//eliminar estudiante
                            int id;
                            cout << "ID del estudiante a eliminar: "; cin >> id;
                            db.eliminarEstudiante(id);
                            break;
                        }
                    }
                } while (opcionEst != 5);
                break;
            }

            // ================== PRESTAMOS ==================
            case 4: {
                int opcionPrestamo;
                do {
                    cout << "\n--- MENU PRESTAMOS ---\n";
                    cout << "1. Registrar Prestamo\n";
                    cout << "2. Devolver Libro\n";
                    cout << "3. Ver Prestamos por Estudiante\n";
                    cout << "4. Volver al menu principal\n";
                    cout << "Opcion: ";
                    cin >> opcionPrestamo;

                    switch (opcionPrestamo) {
                        case 1: { //registramos el prestamo
                            if (db.libros.empty() || db.estudiantes.empty()) {
                                cout << "Necesitas libros y estudiantes registrados.\n";
                                break;
                            }
                            int id_libro, id_estudiante;
                            string fecha;
                            cout << "Libros disponibles:\n"; db.listarLibros();
                            cout << "ID del libro: "; cin >> id_libro;
                            cout << "Estudiantes disponibles:\n"; db.listarEstudiantes();
                            cout << "ID del estudiante: "; cin >> id_estudiante;
                            cout << "Fecha del prestamo (DD-MM-AAAA): "; cin >> fecha;
                            db.prestarLibro(id_libro, id_estudiante, fecha);
                            break;
                        }
                        case 2: { //accion de devolver
                            int id_prestamo, id_estudiante;
                            string fecha;
                            cout << "ID del prestamo: "; cin >> id_prestamo;
                            cout << "ID del estudiante: "; cin >> id_estudiante;
                            cout << "Fecha devolucion (DD-MM-AAAA): "; cin >> fecha;
                            db.devolverLibro(id_prestamo, id_estudiante, fecha);
                            break;
                        }
                        case 3: { //historial de prestamos realizados
                            int id_estudiante;
                            cout << "ID del Estudiante: "; cin >> id_estudiante;
                            db.listarPrestamosPorEstudiante(id_estudiante);
                            break;
                        }
                    }
                } while (opcionPrestamo != 4);
                break;
            }

            // ================== SALIR ==================
            case 5: {//funcionespara txt
                db.guardarAutores();
                db.guardarLibros();
                db.guardarEstudiantes();
                db.guardarPrestamos();
                cout << " Datos guardados. Saliendo...\n";
                break;
            }

            default: cout << " Opcion invalida.\n";
        }
    } while (opcionPrincipal != 5);

    return 0;
}