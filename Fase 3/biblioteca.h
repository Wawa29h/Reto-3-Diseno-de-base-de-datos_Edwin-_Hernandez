#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// ================== ENTIDADES ==================
//creacion de tablas
//los struct sive como registros

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano;
    int id_autor;
    bool disponible = true;
};

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;
    int id_estudiante;
    string fecha_prestamo;
    string fecha_devolucion; 
};

// ================== CLASE PRINCIPAL ==================
class BibliotecaDB {
private: //contadores para generar id automaticos
    int nextLibroId = 1;
    int nextAutorId = 1;
    int nextEstudianteId = 1;
    int nextPrestamoId = 1;

public:
//vectores que simulen las tablas en la memoria
    vector<Libro> libros;
    vector<Autor> autores;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    // ================== AUTORES ==================

    void agregarAutor(string nombre, string nacionalidad) { //comprueba que al agregar el autor valida qeu no esta vacio
        if (nombre.empty()) {
            cout << "Error: El nombre no puede estar vacio.\n";
            return;
        }
        Autor a{nextAutorId++, nombre, nacionalidad};
        autores.push_back(a);
        cout << "Autor agregado con ID: " << a.id << endl;
    }

    void listarAutores() { //lista de  autores registrados
        if (autores.empty()) {
            cout << "No hay autores registrados.\n";
            return;
        }
        for (auto &a : autores) {
            cout << a.id << " - " << a.nombre << " (" << a.nacionalidad << ")\n";
        }
    }

    void actualizarAutor(int id, string nombre, string nacionalidad) { //actualiza los datos del autor por iD
        for (auto &a : autores) {
            if (a.id == id) {
                a.nombre = nombre;
                a.nacionalidad = nacionalidad;
                cout << "Autor actualizado.\n";
                return;
            }
        }
        cout << "Autor no encontrado.\n";
    }
  // elimina un autor por ID
    void eliminarAutor(int id) {
        for (auto it = autores.begin(); it != autores.end(); ++it) {
            if (it->id == id) {
                autores.erase(it);
                cout << "Autor eliminado.\n";
                return;
            }
        }
        cout << "Autor no encontrado.\n";
    }
//Guarda los autores en el txt
    void guardarAutores() {
        ofstream archivo("autores.txt");
        for (auto &a : autores) {
            archivo << a.id << "," << a.nombre << "," << a.nacionalidad << endl;
        }
    }
//Cargar los autores anteriores
    void cargarAutores() {
        ifstream archivo("autores.txt");
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, nombre, nacionalidad;
            getline(ss, id, ',');
            getline(ss, nombre, ',');
            getline(ss, nacionalidad, ',');
            if (id.empty()) continue;
            Autor a{stoi(id), nombre, nacionalidad};
            autores.push_back(a);
            if (a.id >= nextAutorId) nextAutorId = a.id + 1;
        }
    }

    // ================== LIBROS ==================
    //agregar libro comprobando si el autor existe y cumple los requisitos minimos
    void agregarLibro(string titulo, string isbn, int ano, int id_autor) {
        if (titulo.empty() || isbn.empty()) {
            cout << "Error: El titulo e ISBN no pueden estar vacios.\n";
            return;
        }
        for (auto &lib : libros) {
            if (lib.isbn == isbn) {
                cout << "Error: ISBN duplicado.\n";
                return;
            }
        }
        bool autorExiste = false;
        for (auto &a : autores) {
            if (a.id == id_autor) { autorExiste = true; break; }
        }
        if (!autorExiste) {
            cout << "Error: Autor no encontrado.\n";
            return;
        }
        Libro l{nextLibroId++, titulo, isbn, ano, id_autor, true};
        libros.push_back(l);
        cout << "Libro agregado con ID: " << l.id << endl;
    }
//lista con con los libros y su respectiva informacion
    void listarLibros() {
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
            return;
        }
        for (auto &lib : libros) {
            string autor = "Desconocido";
            for (auto &a : autores) {
                if (a.id == lib.id_autor) {
                    autor = a.nombre;
                    break;
                }
            }
            cout << lib.id << " - " << lib.titulo << " (" << lib.ano << ") "
                 << (lib.disponible ? "[Disponible]" : "[Prestado]")
                 << " | Autor: " << autor << " | ISBN: " << lib.isbn << endl;
        }
    }
//actualizar libros por ID
    void actualizarLibro(int id, string titulo, string isbn, int ano) {
        for (auto &lib : libros) {
            if (lib.id == id) {
                lib.titulo = titulo;
                lib.isbn = isbn;
                lib.ano = ano;
                cout << "Libro actualizado.\n";
                return;
            }
        }
        cout << "Libro no encontrado.\n";
    }
//eliminar libros por iD
    void eliminarLibro(int id) {
        for (auto it = libros.begin(); it != libros.end(); ++it) {
            if (it->id == id) {
                libros.erase(it);
                cout << "Libro eliminado.\n";
                return;
            }
        }
        cout << "Libro no encontrado.\n";
    }
//guardar libros al txt
    void guardarLibros() {
        ofstream archivo("libros.txt");
        for (auto &lib : libros) {
            archivo << lib.id << "," << lib.titulo << "," << lib.isbn << ","
                    << lib.ano << "," << lib.id_autor << "," << lib.disponible << endl;
        }
    }
//cargar libros desde archivo guardado
    void cargarLibros() {
        ifstream archivo("libros.txt");
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, titulo, isbn, ano, id_autor, disponible;
            getline(ss, id, ','); getline(ss, titulo, ','); getline(ss, isbn, ',');
            getline(ss, ano, ','); getline(ss, id_autor, ','); getline(ss, disponible, ',');
            if (id.empty()) continue;
            Libro l{stoi(id), titulo, isbn, stoi(ano), stoi(id_autor), (disponible == "1")};
            libros.push_back(l);
            if (l.id >= nextLibroId) nextLibroId = l.id + 1;
        }
    }

    // ================== ESTUDIANTES ==================
    void agregarEstudiante(string nombre, string grado) {     // Lista de todos los estudiantes
        if (nombre.empty()) {
            cout << "Error: El nombre del estudiante no puede estar vacio.\n";
            return;
        }
        for (auto &e : estudiantes) {
            if (e.nombre == nombre) {
                cout << "Error: Estudiante duplicado.\n";
                return;
            }
        }
        Estudiante e{nextEstudianteId++, nombre, grado};
        estudiantes.push_back(e);
        cout << "Estudiante agregado con ID: " << e.id << endl;
    }
//mostrar estudiantes registrados
    void listarEstudiantes() {
        if (estudiantes.empty()) {
            cout << "No hay estudiantes registrados.\n";
            return;
        }
        for (auto &e : estudiantes) {
            cout << e.id << " - " << e.nombre << " | Grado: " << e.grado << endl;
        }
    }
 //Actualizar estudiantes por ID
    void actualizarEstudiante(int id, string nombre, string grado) {
        for (auto &e : estudiantes) {
            if (e.id == id) {
                e.nombre = nombre;
                e.grado = grado;
                cout << "Estudiante actualizado.\n";
                return;
            }
        }
        cout << "Estudiante no encontrado.\n";
    }
// Elimina un estudiante por ID
    void eliminarEstudiante(int id) {
        for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
            if (it->id == id) {
                estudiantes.erase(it);
                cout << "Estudiante eliminado.\n";
                return;
            }
        }
        cout << "Estudiante no encontrado.\n";
    }
//guarda un txt con los estudiantes
    void guardarEstudiantes() {
        ofstream archivo("estudiantes.txt");
        for (auto &e : estudiantes) {
            archivo << e.id << "," << e.nombre << "," << e.grado << endl;
        }
    }
//carga desde el txt
    void cargarEstudiantes() {
        ifstream archivo("estudiantes.txt");
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, nombre, grado;
            getline(ss, id, ','); getline(ss, nombre, ','); getline(ss, grado, ',');
            if (id.empty()) continue;
            Estudiante e{stoi(id), nombre, grado};
            estudiantes.push_back(e);
            if (e.id >= nextEstudianteId) nextEstudianteId = e.id + 1;
        }
    }

    // ================== PRESTAMOS ==================

    //registra un prestamo validando que esta disponible y que el estudiante no lo tenga
    void prestarLibro(int id_libro, int id_estudiante, string fecha) {
        for (auto &p : prestamos) {
            if (p.id_libro == id_libro && p.id_estudiante == id_estudiante && p.fecha_devolucion.empty()) {
                cout << "Error: Este estudiante ya tiene prestado este libro.\n";
                return;
            }
        }
        for (auto &lib : libros) {
            if (lib.id == id_libro) {
                if (!lib.disponible) {
                    cout << "El libro ya esta prestado.\n";
                    return;
                }
                lib.disponible = false;
                Prestamo p{nextPrestamoId++, id_libro, id_estudiante, fecha, ""};
                prestamos.push_back(p);
                cout << "Prestamo registrado con ID: " << p.id << endl;
                return;
            }
        }
        cout << "Libro no encontrado.\n";
    }
// marcar el estado del prestamo
    void devolverLibro(int id_prestamo, int id_estudiante, string fecha) {
        for (auto &p : prestamos) {
            if (p.id == id_prestamo && p.id_estudiante == id_estudiante && p.fecha_devolucion.empty()) {
                p.fecha_devolucion = fecha;
                for (auto &lib : libros) {
                    if (lib.id == p.id_libro) lib.disponible = true;
                }
                cout << "Libro devuelto por estudiante " << id_estudiante << ".\n";
                return;
            }
        }
        cout << "Error: Prestamo no encontrado o ya devuelto.\n";
    }
// lista de usuarios/estudiantes
    void listarPrestamosPorEstudiante(int id_estudiante) {
        cout << "Historial del estudiante " << id_estudiante << ":\n";
        for (auto &p : prestamos) {
            if (p.id_estudiante == id_estudiante) {
                for (auto &lib : libros) {
                    if (lib.id == p.id_libro) {
                        cout << "- " << lib.titulo << " | Prestado el: " << p.fecha_prestamo
                             << (p.fecha_devolucion.empty() ? " [No devuelto]" : " | Devuelto el: " + p.fecha_devolucion)
                             << endl;
                    }
                }
            }
        }
    }
//guarda los prestamos en un txt
    void guardarPrestamos() {
        ofstream archivo("prestamos.txt");
        for (auto &p : prestamos) {
            archivo << p.id << "," << p.id_libro << "," << p.id_estudiante << ","
                    << p.fecha_prestamo << "," << p.fecha_devolucion << endl;
        }
    }
//carga los anteriores prestamos
    void cargarPrestamos() {
        ifstream archivo("prestamos.txt");
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string id, id_libro, id_estudiante, fecha_prestamo, fecha_devolucion;
            getline(ss, id, ','); getline(ss, id_libro, ','); getline(ss, id_estudiante, ',');
            getline(ss, fecha_prestamo, ','); getline(ss, fecha_devolucion, ',');
            if (id.empty()) continue;
            Prestamo p{stoi(id), stoi(id_libro), stoi(id_estudiante), fecha_prestamo, fecha_devolucion};
            prestamos.push_back(p);
            if (p.id >= nextPrestamoId) nextPrestamoId = p.id + 1;
        }
    }
};
