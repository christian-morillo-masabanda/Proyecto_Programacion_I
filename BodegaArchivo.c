#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 10
#define MAX_PRODUCTOS 5

int numClientes = 0;
int numProductos[MAX_CLIENTES] = {0};

char ownerNames[MAX_CLIENTES][50];
char ownerCellphones[MAX_CLIENTES][20];
char ownerEmails[MAX_CLIENTES][50];
char ownerAddresses[MAX_CLIENTES][50];
char ClientesIDs[MAX_CLIENTES][11];
char productNames[MAX_CLIENTES][MAX_PRODUCTOS][50];
char productQuantities[MAX_CLIENTES][MAX_PRODUCTOS][20];
float productValues[MAX_CLIENTES][MAX_PRODUCTOS];

void addProduct();
void viewProducts();
void generateID(char *id);
void saveData();
void loadData();

int main(int argc, char *argv[]) {
    int choice;
    srand(time(NULL));

    // Cargar los datos desde el archivo
    loadData();

    while (1) {
        printf("*****Almacenes de todo*****\n");
        printf("Menu de opciones:\n");
        printf("1. Agregar Cliente\n");
        printf("2. Ver productos\n");
        printf("3. Salir\n");
        printf("Ingresar opcion: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                printf("*****Gracias por usar la bodega****");
                // Guardar los datos en el archivo antes de salir
                saveData();
                exit(0);
        }
    }
}

void generateID(char *id) {
    id[0] = 'A' + rand() % 26;
    id[1] = 'A' + rand() % 26;
    for (int i = 2; i < 10; i++) {
        id[i] = '0' + rand() % 10;
    }
    id[10] = '\0';
}

void addProduct() {
    if (numClientes == MAX_CLIENTES) {
        printf("No se pueden agregar más clientes.\n");
        return;
    }

    if (numProductos[numClientes] == MAX_PRODUCTOS) {
        printf("No se pueden agregar más productos para este cliente.\n");
        return;
    }

    printf("\n");
    printf("Ingrese el nombre del Arrendador %d: ", numClientes + 1);
    getchar();
    gets(ownerNames[numClientes]);
    printf("Ingrese el celular del Arrendador %d: ", numClientes + 1);
    gets(ownerCellphones[numClientes]);
    printf("Ingrese el correo del Arrendador %d: ", numClientes + 1);
    gets(ownerEmails[numClientes]);
    printf("Ingrese la direccion del Arrendador %d: ", numClientes + 1);
    gets(ownerAddresses[numClientes]);

    int numProducts;
    printf("Ingrese el numero de productos que desea guardar (1-5): ");
    scanf("%d", &numProducts);
    getchar();  

    if (numProducts < 1 || numProducts > 5) {
        printf("Número de productos inválido.\n");
        return;
    }

    for (int i = 0; i < numProducts; i++) {
        printf("Ingrese el nombre del producto %d: ", i + 1);
        gets(productNames[numClientes][i]);
        printf("Ingrese las unidades del producto %d: ", i + 1);
        gets(productQuantities[numClientes][i]);
        printf("Ingrese el valor unitario del producto %d: ", i + 1);
        scanf("%f", &productValues[numClientes][i]);
        getchar();  
    }

    generateID(ClientesIDs[numClientes]);

    numProductos[numClientes] = numProducts;
    numClientes++;
    printf("\n");
    printf("********Producto(s) agregado(s) exitosamente********\n\n");
}

void viewProducts() {
    int i, j;
    if (numClientes == 0) {
        printf("No hay clientes para mostrar.\n");
        return;
    }

    for (i = 0; i < numClientes; i++) {
        printf("\n");
        printf("*****Datos del Arrendador y sus productos:*****\n\n");
        printf("ID del cliente: %s\n", ClientesIDs[i]);
        printf("Nombre del arrendador: %s\n", ownerNames[i]);
        printf("Celular del arrendador: %s\n", ownerCellphones[i]);
        printf("Correo del arrendador: %s\n", ownerEmails[i]);
        printf("Direccion del arrendador: %s\n", ownerAddresses[i]);

        if (numProductos[i] == 0) {
            printf("No hay productos para mostrar.\n");
        } else {
            printf("Productos:\n");
            float totalValue = 0.0;
            for (j = 0; j < numProductos[i]; j++) {
                printf("Producto %d:\n", j + 1);
                printf("  Nombre: %s\n", productNames[i][j]);
                printf("  Cantidad: %s\n", productQuantities[i][j]);
                printf("  Valor: %.2f\n", productValues[i][j]);
                float cantidad, valor;
                sscanf(productQuantities[i][j], "%f", &cantidad);
                valor = productValues[i][j];
                totalValue += cantidad * valor;
            }
            printf("Valor total: %.2f\n", totalValue);
        }
    }
}

void saveData() {
    FILE *file = fopen("clientes.dat", "wb");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fwrite(&numClientes, sizeof(int), 1, file);
    fwrite(numProductos, sizeof(int), MAX_CLIENTES, file);
    fwrite(ownerNames, sizeof(char), MAX_CLIENTES * 50, file);
    fwrite(ownerCellphones, sizeof(char), MAX_CLIENTES * 20, file);
    fwrite(ownerEmails, sizeof(char), MAX_CLIENTES * 50, file);
    fwrite(ownerAddresses, sizeof(char), MAX_CLIENTES * 50, file);
    fwrite(ClientesIDs, sizeof(char), MAX_CLIENTES * 11, file);
    fwrite(productNames, sizeof(char), MAX_CLIENTES * MAX_PRODUCTOS * 50, file);
    fwrite(productQuantities, sizeof(char), MAX_CLIENTES * MAX_PRODUCTOS * 20, file);
    fwrite(productValues, sizeof(float), MAX_CLIENTES * MAX_PRODUCTOS, file);

    fclose(file);
}

void loadData() {
    FILE *file = fopen("clientes.dat", "rb");
    if (file == NULL) {
        printf("No se encontró el archivo de datos.\n");
        return;
    }

    fread(&numClientes, sizeof(int), 1, file);
    fread(numProductos, sizeof(int), MAX_CLIENTES, file);
    fread(ownerNames, sizeof(char), MAX_CLIENTES * 50, file);
    fread(ownerCellphones, sizeof(char), MAX_CLIENTES * 20, file);
    fread(ownerEmails, sizeof(char), MAX_CLIENTES * 50, file);
    fread(ownerAddresses, sizeof(char), MAX_CLIENTES * 50, file);
    fread(ClientesIDs, sizeof(char), MAX_CLIENTES * 11, file);
    fread(productNames, sizeof(char), MAX_CLIENTES * MAX_PRODUCTOS * 50, file);
    fread(productQuantities, sizeof(char), MAX_CLIENTES * MAX_PRODUCTOS * 20, file);
    fread(productValues, sizeof(float), MAX_CLIENTES * MAX_PRODUCTOS, file);

    fclose(file);
}