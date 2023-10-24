#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
char read_buff; // Karakterleri okumak i�in a�ilan char
char temp_str[128] = {0}; //Belirleyici virg�le kadar okumas�n� sa�l�yor
int temp_str_ptr = 0; // Malloc i�inde de�i�ken boyutland�r�c�
char *csv_header_array[32]; // Headerlari tutan char pointer arrayi
int header_ptr = 0; //Header arrayinin i�indeki de�i�ken
char header_on = 0; // Header kontrolc�s�
char indent = 0; //Json dosyas�n�n ba��na konacak "{" �n bir kere konmas� i�in kontrolc�

FILE *output_file;
FILE *input_file;

// headerlar� bulup belle�e kaydeden fonksiyon
void add_header(char *header){
    printf("%s",header);
    csv_header_array[header_ptr] = (char *) malloc((temp_str_ptr+1) * sizeof(char));
    strcpy(csv_header_array[header_ptr++],header);
}

// De�erleri json dosyas�na yazd�ran fonksiyon
void print_json(char* value){
    if(!strcmp(value,"")) return;
    fprintf(output_file, "\t\t\"%s\"", value);
}

// Header de�erlerini json dosyas�na yazd�ran fonksiyon
void print_json_header(char* header, char* value){
    if(!strcmp(value,"")) return;
    fprintf(output_file, "\t\t%s:\"%s\"", header, value);
}

// Kullan�c�n�n arg�mana girdi�i header=On veya Header=Off de�erindi kontorl edip Off ise Headers�z dosya convertinin �al��t��� k�s�m.
void check_headers(char* header_option){
    if(!strcmp(header_option,"header=ON")){
        header_on = 1;
        while ((read_buff = getc(input_file)) != '\n') {
            if (read_buff != ',') {
                temp_str[temp_str_ptr++] = read_buff;
            } else if  (read_buff == ',') {
                temp_str[temp_str_ptr] = '\0';
                add_header(temp_str);
                header_ptr++;
                temp_str_ptr = 0;
            }
        }
        if (read_buff == '\n') {
            temp_str[temp_str_ptr] = '\0';
            printf("%s",temp_str);
            add_header(temp_str);
            temp_str_ptr = 0;
            header_ptr = 0;
        }
    }
    return;
}
// Kullan�c�n�n arg�mana girdi�i header=On veya Header=Off de�erindi kontorl edip On ise Headerl� dosya convertinin �al��t��� k�s�m. (Ayn� zamandaT�m fonksiyonlar�n kullan�l�d��� main alan�)
int main(int argc, char **argv) {
	input_file = fopen(argv[1], "r");
	output_file = fopen(argv[2], "w");
    check_headers(argv[3]);
    fprintf(output_file, "{\n");
    while ((read_buff = getc(input_file)) != EOF) {
        if (indent == 0) {
            fprintf(output_file, "\t{\n");
            indent = 1;
            
        }
        if (read_buff != ',' && read_buff != '\n') {
            temp_str[temp_str_ptr++] = read_buff;
        } else if (read_buff == ',') {
            temp_str[temp_str_ptr] = '\0';
            temp_str_ptr = 0;
            if(header_on){
                print_json_header(csv_header_array[header_ptr++],temp_str);
                fprintf(output_file,",\n");
            }
            else{
                print_json(temp_str);
                fprintf(output_file,",\n");
            }
            header_ptr++;
        } else if  (read_buff == '\n') {
            temp_str[temp_str_ptr] = '\0';
            temp_str_ptr = 0;
            if(header_on){
                print_json_header(csv_header_array[header_ptr++],temp_str);
                fprintf(output_file,"\n\t},\n");
            }
            else{
                print_json(temp_str);
                fprintf(output_file,"\n\t},\n");
            }         
            header_ptr = 0;
            indent = 0;
        }
    }
    temp_str[temp_str_ptr] = '\0';
    
    if(header_on)
        print_json_header(csv_header_array[header_ptr++],temp_str);
    else
        print_json(temp_str);           
    
    fprintf(output_file, "}");

    fclose(output_file);
    
    fclose(input_file);
    return 0;
}

