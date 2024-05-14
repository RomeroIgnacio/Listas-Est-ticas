#include <iostream>
#include <string>

using namespace std;

const int TAM = 3;

enum
{
    AGREGAR = 1,
    BUSCAR,
    ELIMINAR,
    INSERTAR,
    MOSTRAR,
    SALIR
};

class Empleado
{
private:
    int ClaveEmpleado;
    string Nombre;
    string Domicilio;
    float Sueldo;
    string ReporteA;

public:
    Empleado() : ClaveEmpleado(0), Nombre(""), Domicilio(""), Sueldo(0), ReporteA("") {}
    Empleado(int clave, string nom, string dom, float sal, string repA) : ClaveEmpleado(clave), Nombre(nom), Domicilio(dom), Sueldo(sal), ReporteA(repA) {}

    friend istream& operator >> (istream& in, Empleado& emp)
    {
        cout << endl << "Ingrese la Clave del Empleado: ";
        in >> emp.ClaveEmpleado;

        cout << "Ingrese el Nombre: ";
        in.ignore();
        getline(in, emp.Nombre);

        cout << "Ingrese el Domicilio: ";
        getline(in, emp.Domicilio);

        cout << "Ingrese el Sueldo: ";
        in >> emp.Sueldo;

        cout << "Ingrese el ReporteA: ";
        in.ignore();
        getline(in, emp.ReporteA);

        return in;
    }

    friend ostream& operator << (ostream& out, const Empleado& emp)
    {
        out << endl << "Clave del Empleado: " << emp.ClaveEmpleado << endl << "Nombre: " << emp.Nombre << endl << "Domicilio: " << emp.Domicilio << endl << "Sueldo: " << emp.Sueldo << endl << "ReporteA: " << emp.ReporteA << endl;

        return out;
    }

    int getClave() const
    {
        return ClaveEmpleado;
    }

    void muestra() const
    {
        cout << endl << "Clave: " << ClaveEmpleado << ", Nombre: " << Nombre << ", Domicilio: " << Domicilio << ", Sueldo: " << Sueldo << ", Reporte: " << ReporteA << endl;
    }
};

class ListaEmpleados
{
private:
    Empleado empleados[TAM];
    int ult;

public:
    ListaEmpleados() : ult(-1), empleados{} {}

    bool vacia() const
    {
        return ult == -1;
    }

    bool llena() const
    {
        return ult == TAM - 1;
    }

    void agregarEmpleado(const Empleado& empleado)
    {
        if (llena()) {
            cout << endl << "Error: la lista de empleados está llena." << endl;
        }
        else
        {
            ult++;
            empleados[ult] = empleado;
            cout << endl << "Empleado agregado correctamente." << endl;
        }
    }

    void mostrarEmpleados() const
    {
        if (vacia())
        {
            cout << endl << "No hay empleados para mostrar." << endl;
        }
        else
        {
            cout << endl << "Lista de Empleados:" << endl;
            for (int i = 0; i <= ult; ++i)
            {
                empleados[i].muestra();
            }
        }
    }

    void buscarEmpleado(int clave) const
    {
        bool encontrado = false;
        for (int i = 0; i <= ult; ++i)
        {
            if (empleados[i].getClave() == clave)
            {
                cout << endl << "Empleado encontrado:" << endl;
                cout << empleados[i];

                encontrado = true;
                break;
            }
        }
        if (!encontrado)
        {
            cout << endl << "Empleado no encontrado." << endl;
        }
    }

    void eliminarEmpleado(int clave)
    {
        bool encontrado = false;
        for (int i = 0; i <= ult; ++i)
        {
            if (empleados[i].getClave() == clave)
            {
                for (int j = i; j < ult; ++j)
                {
                    empleados[j] = empleados[j + 1];
                }
                ult--;
                encontrado = true;
                cout << endl << "Empleado eliminado correctamente." << endl;
                break;
            }
        }
        if (!encontrado)
        {
            cout << endl << "Empleado no encontrado." << endl;
        }
    }

    void insertarEmpleado(const Empleado& empleado, int pos)
    {
        if (llena())
        {
            cout << endl << "Error: la lista de empleados está llena." << endl;
        }
        else if (pos < 0 || pos > ult + 1)
        {
            cout << endl << "No se puede insertar en la posición especificada." << endl;
        }
        else
        {
            if (pos == ult + 1)
            {
                empleados[pos] = empleado;
                ult++;
                cout << endl << "Empleado insertado correctamente." << endl;
            }
            else
            {
                for (int i = ult + 1; i > pos; --i)
                {
                    empleados[i] = empleados[i - 1];
                }
                empleados[pos] = empleado;
                ult++;
                cout << endl << "Empleado insertado correctamente." << endl;
            }
        }
    }
};

void menu()
{
    cout << endl << "Menu:" << endl << " " << 
    AGREGAR << ") Agregar Empleado" << endl << " " << 
    BUSCAR << ") Buscar Empleado" << endl << " " << 
    ELIMINAR << ") Eliminar Empleado" << endl << " " << 
    INSERTAR << ") Insertar Empleado" << endl << " " << 
    MOSTRAR << ") Mostrar Empleados" << endl << " " << 
    SALIR << ") Salir" << endl << 
    "Ingresa una opción: ";
}

int main()
{
    ListaEmpleados listaEmpleados;

    int op;
    do
    {
        menu();
        cin >> op;

        switch (op)
        {
            case AGREGAR:
            {
                Empleado empleado;
                cin >> empleado;
                listaEmpleados.agregarEmpleado(empleado);
                break;
            }

            case BUSCAR:
            {
                int clave;
                cout << endl << "Ingrese la clave del empleado a buscar: ";
                cin >> clave;
                listaEmpleados.buscarEmpleado(clave);
                break;
            }

            case ELIMINAR:
            {
                int clave;
                cout << endl << "Ingrese la clave del empleado a eliminar: ";
                cin >> clave;
                listaEmpleados.eliminarEmpleado(clave);
                break;
            }

            case INSERTAR:
            {
                int pos;
                cout << endl << "Ingrese la posición donde desea insertar el empleado: ";
                cin >> pos;
                Empleado empleado;
                cin >> empleado;
                listaEmpleados.insertarEmpleado(empleado, pos);
                break;
            }

            case MOSTRAR:
            {
                listaEmpleados.mostrarEmpleados();
                break;
            }

            case SALIR:
            {
                cout << endl << "Saliendo del Programa" << endl;
                return 0;
            }

            default:
            {
                cout << endl << "Opción no válida" << endl;
            }
        }
    }
    while (1);

    return 0;
}