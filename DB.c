/* DB.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

// Function to initialize the picnic table database
void initializePicnicTable(Database *db, int initialSize) {
    // Allocate memory for the picnicTables array
    db->picnicTables = (PicnicTable *)malloc(initialSize * sizeof(PicnicTable));
    if (db->picnicTables == NULL) {
        perror("Error allocating memory for picnic tables");
        exit(1);  // Exit if memory allocation fails
    }

    // Set the initial picnicTable count to 0
    db->picnicTableCount = 0;
}

// Function to cleanup memory when done
void freePicnicTable(Database *db) {
    if (db->picnicTables != NULL) {
        free(db->picnicTables);  // Free the memory allocated for picnic tables
        db->picnicTables = NULL; // Set the pointer to NULL to avoid dangling pointer
    }
}


// Function to read a CSV file and populate the picnicTables array
void importDB(Database *db, const char *filename) {
    FILE *file = fopen(filename, "r");  // Open the CSV file for reading
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[1024];  // Buffer to hold each line of the file
    int tableId = 1;  // Unique table ID for picnic table entry

    // Skip the header line 
    fgets(line, sizeof(line), file); 

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        PicnicTable table;

        // Parse the CSV line 
        char *token = strtok(line, ","); // Tokenize the line by commas

        
        table.siteId = atoi(token);  // Parse siteId as integer
        token = strtok(NULL, ",");   // Move to the next token
        strcpy(table.tableType, token);  // Store Table Type

        token = strtok(NULL, ",");
        strcpy(table.surfaceMaterial, token);  // Store Surface Material

        token = strtok(NULL, ",");
        strcpy(table.structuralMaterial, token);  // Store Structural Material

        token = strtok(NULL, ",");
        strcpy(table.streetAvenue, token);  // Store Street/Avenue

        token = strtok(NULL, ",");
        table.neighbhdId = atoi(token);  // Parse Neighbourhood Id

        token = strtok(NULL, ",");
        strcpy(table.neighbourhoodName, token);  // Store Neighbourhood Name

        token = strtok(NULL, ",");
        table.ward = atoi(token);  // Parse Ward

        token = strtok(NULL, ",");
        strcpy(table.latitude, token);  // Store Latitude as string 

        token = strtok(NULL, ",");
        strcpy(table.longitude, token);  // Store Longitude as string 

        // Add the new table entry to the picnicTable array
        db->picnicTables[db->picnicTableCount] = table;
        db->picnicTableCount++;

        // If array is full, you can reallocate memory to expand the picnicTables array
        if (db->picnicTableCount >= db->picnicTableCount) {
            db->picnicTables = realloc(db->picnicTables, (db->picnicTableCount + 10) * sizeof(PicnicTable));
        }
    }

    fclose(file);  // Close the file after reading
}

// Main function for testing
int main() {
    // Create a Database object
    Database db;

    
    

    // Initialize the picnic table array with an initial size of 10
    //initializePicnicTable(&db, 10);

    // Import data from the CSV file
    //importDB(&db, "PicnicTable.csv");

    // Print out the first entry to check if it's populated correctly
    //printf("First picnic table - Site ID: %d, Table Type: %s\n");
        //db.picnicTables[0].siteId, db.picnicTables[0].tableType);

    // Free allocated memory
   // freePicnicTable(&db);
    return 0;
}