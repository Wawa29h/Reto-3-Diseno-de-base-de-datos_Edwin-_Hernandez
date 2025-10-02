Este es un sistema de gestión de biblioteca desarrollado en C++, que permite manejar autores, libros, estudiantes y préstamos.
El programa utiliza structs para representar las entidades principales y vectores en memoria para almacenar la información, con persistencia en archivos .txt.

------------Funcionalidades----------------

El sistema permite realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) para:

-Autores
Agregar, listar, actualizar y eliminar autores.

-Libros
Agregar, listar, actualizar y eliminar libros.
Los libros están asociados a un autor y pueden estar disponibles o prestados.

-Estudiantes
Agregar, listar, actualizar y eliminar estudiantes.

-Préstamos
Registrar un préstamo de libro.
Evita préstamos duplicados del mismo libro al mismo estudiante.
Devolver libros, registrando fecha de devolución.

-Ver los distintos historiales.

----------------------------Tecnologias implementadas------------------------
En este proyecto utilizamos distintas tecnologias para el correcto funcionamiento:
Lenguaje: C++17

Librerías estándar:
<iostream>
<fstream>
<sstream>
<vector>
<string>

------Intrucciones para correr el programa--------------
Cómo correr el programa

Abre una terminal en la carpeta donde están los archivos main.cpp y biblioteca.h.

Compila el programa con el siguiente comando:
g++ main.cpp -o biblioteca

Si no hay errores de compilación, se generará un archivo ejecutable llamado biblioteca.

Ejecuta el programa con el comando:
./biblioteca

Se abrirá el menú principal en la terminal y podrás navegar por las opciones.


----Intrucciones de uso-------

Una vez el programa este corriendo veremos un menu como este:

Menú Principal
===== MENU BIBLIOTECA =====

1.Gestionar Autores
2.Gestionar Libros
3.Gestionar Estudiantes
4.Gestionar Prestamos
5.Guardar y Salir

Cada opción abre un submenú con las operaciones correspondientes.

Estructura de Archivos
=main.cpp → Contiene el menú principal y la lógica de interacción con el usuario.
=biblioteca.h → Define las entidades y métodos de gestión (autores, libros, estudiantes, préstamos).
=README.md → Documentación del proyecto.
=autores.txt → Datos de autores.
=libros.txt → Datos de libros.
=estudiantes.txt → Datos de estudiantes.
=prestamos.txt → Datos de préstamos.

