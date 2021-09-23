#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ListaVariacionNegativo();
void ArchivoCsv();
void TablaHtml();

void substr(char*, char*, int, int);
int get_index(char*, const char*);
int get_indexes(const char *, const char*, int);

int removeChar(char*, char );
int replacechar(char *, char, char);

int main()
{
    int opcion = 0;

    while(opcion != 4){
        printf("Elegir una opcion\n\n");
        printf("1- Lista de especies con porcentaje de variacion negativo\n");
        printf("2- Listado de cotizaciones en archivo CSV\n");
        printf("3- Lista de especies en HTML\n");
        printf("4- Salir\n");

        scanf("%d", &opcion);

        switch(opcion) {
          case 1 :
             ListaVariacionNegativo();
             break;
          case 2 :
             ArchivoCsv();
             break;
          case 3 :
             TablaHtml();
             break;
       }

       printf("\n");
    }

    return 0;
}

void ListaVariacionNegativo(){
    FILE *f  = fopen("SSL-TP2.html", "r");

    printf("\n");
    printf("Lista de especies con porcentaje de variacion negativo\n\n");

    const char filaContado[] = "<td style=\"text-align: center;\">Cdo.</td>";
    const char filaNegativa[] = "<span style=\"color:#e94b46;\">";
    const char inicioNombre[] = "data-order=\"";
    const char finNombre[] = "onclick=\"link('";
    char sub[10] = "";
    char *retfilaContado;
    char *retfilaNegativa;

    char result[1000];

    while(fgets(result, sizeof(result), f) != NULL){

        retfilaContado = strstr(result, filaContado);
        if (retfilaContado){
            retfilaNegativa = strstr(result, filaNegativa);
            if (retfilaNegativa){
                int i = get_index(result, inicioNombre);
                int j = get_index(result, finNombre);

                int offset = strlen(inicioNombre);
                int index = i + offset;

                substr(result, sub, index, j - index - 2);

                printf("%s\n", sub);
            }
        }
    }

    fclose(f);
}

void ArchivoCsv(){
    FILE *f  = fopen("SSL-TP2.html", "r");

    FILE *f2;

    f2 = fopen("archivo.csv", "w");

    const char filaContado[] = "<td style=\"text-align: center;\">Cdo.</td>";
    const char td[] = "</td><td>";
    const char header[] = "Especie;Precio de compra;Precio de venta;Apertura;Precio Máximo;Precio Mínimo\n";
    char precioCompra[5] = "";
    char precioVenta[5] = "";
    char nombre[5] = "";
    char apertura[5] = "";
    char minimo[5] = "";
    char maximo[5] = "";
    const char inicioNombre[] = "data-order=\"";
    const char finNombre[] = "onclick=\"link('";
    char *retfilaContado;

    char result[1000];

    fprintf(f2, "%s", header);

    while(fgets(result, sizeof(result), f) != NULL){

        retfilaContado = strstr(result, filaContado);
        if (retfilaContado){
            int i = get_index(result, inicioNombre);
            int j = get_index(result, finNombre);

            int offset = strlen(inicioNombre);
            int index = i + offset;

            substr(result, nombre, index, j - index - 2);

            fprintf(f2, "%s;", nombre);

            i = get_indexes(result, td, 1);
            j = get_indexes(result, td, 2);

            offset = strlen(td);
            index = i + offset;

            substr(result, precioCompra, index, j - index);

            fprintf(f2, "%s;", precioCompra);

            i = get_indexes(result, td, 2);
            j = get_indexes(result, td, 3);

            offset = strlen(td);
            index = i + offset;

            substr(result, precioVenta, index, j - index);

            fprintf(f2, "%s;", precioVenta);

            i = get_indexes(result, td, 6);
            j = get_indexes(result, td, 7);

            offset = strlen(td);
            index = i + offset;

            substr(result, apertura, index, j - index);

            fprintf(f2, "%s;", apertura);

            i = get_indexes(result, td, 8);
            j = get_indexes(result, td, 9);

            offset = strlen(td);
            index = i + offset;

            substr(result, maximo, index, j - index);

            fprintf(f2, "%s;", maximo);

            i = get_indexes(result, td, 7);
            j = get_indexes(result, td, 8);

            offset = strlen(td);
            index = i + offset;

            substr(result, minimo, index, j - index);

            fprintf(f2, "%s;\n", minimo);
        }
    }

    fclose(f);
    fclose(f2);

    printf("\n");
    printf("Archivo csv generado\n\n");
}

void TablaHtml(){
    FILE *f  = fopen("SSL-TP2.html", "r");

    FILE *f2;
    f2 = fopen("listado.html", "w");

    const char filaContado[] = "<td style=\"text-align: center;\">Cdo.</td>";
    const char td[] = "</td><td>";
    const char inicioNombre[] = "data-order=\"";
    const char finNombre[] = "onclick=\"link('";

    char nombre[10] = "";
    char precioCompra[10] = "";
    char precioVenta[10] = "";
    char apertura[10] = "";
    char *retfilaContado;

    char result[1000];

    const char header[] = "<table><tr><th>Especie</th></tr>";
    const char row[] = "<tr style=\"background-color: #10da10;\"><td>";
    const char endRow[] = "</td></tr>";
    const char endTable[] = "</table>";

    fprintf(f2, "%s", header);

    while(fgets(result, sizeof(result), f) != NULL){

        retfilaContado = strstr(result, filaContado);
        if (retfilaContado){

            int i = get_index(result, inicioNombre);
            int j = get_index(result, finNombre);

            int offset = strlen(inicioNombre);
            int index = i + offset;

            substr(result, nombre, index, j - index - 2);

            i = get_indexes(result, td, 1);
            j = get_indexes(result, td, 2);

            offset = strlen(td);
            index = i + offset;

            substr(result, precioCompra, index, j - index);

            i = get_indexes(result, td, 2);
            j = get_indexes(result, td, 3);

            offset = strlen(td);
            index = i + offset;

            substr(result, precioVenta, index, j - index);

            i = get_indexes(result, td, 6);
            j = get_indexes(result, td, 7);

            offset = strlen(td);
            index = i + offset;

            substr(result, apertura, index, j - index);

            removeChar(precioCompra, '.');
            replacechar(precioCompra, ',', '.');

            removeChar(precioVenta, '.');
            replacechar(precioVenta, ',', '.');

            removeChar(apertura, '.');
            replacechar(apertura, ',', '.');

            float fCompra = atof(precioCompra);
            float fVenta = atof(precioVenta);
            float fApertura = atof(apertura);

            if (fCompra < fApertura && fVenta < fApertura){

                fprintf(f2, "%s", row);

                fprintf(f2, "%s", nombre);

                fprintf(f2, "%s", endRow);
            }
        }
    }

    fprintf(f2, "%s", endTable);

    fclose(f);
    fclose(f2);

    printf("\n");
    printf("Archivo html generado\n\n");
}

int replacechar(char *str, char orig, char rep) {
    char *ix = str;
    int n = 0;
    while((ix = strchr(ix, orig)) != NULL) {
        *ix++ = rep;
        n++;
    }
    return n;
}

int get_index(char* str, const char* find) {
    char *result = strstr(str, find);
    int position = result - str;

    return position;
}

int get_indexes(const char *str, const char* find, int i)
{
    const char *ptr = str;
    int count = 0;
    while ((ptr = strstr(ptr, find)) != NULL && count < i) {
        ptr += 9;
        count++;
    }

    int position = ptr - str;

    return position;
}

void substr(char* str, char* sub , int start, int len){
    memcpy(sub, &str[start], len);
    sub[len] = '\0';
}

int removeChar(char *str, char c) {

    int i, j;

    for(i = 0, j = 0 ; str[i] ; i++){
        if( str[i] == c) continue;
        str[j] = str[i];
        j++;
    }
    str[j]=0;
    return j;
}
