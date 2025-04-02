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
#include <ctype.h>

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

// Function to lookup values from a specific table in the db
int findCodeFromLookupTable(LookupTable *table, const char *value) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->entries[i].value, value) == 0) {
            return table->entries[i].code;
        }
    }
    
    //If the value doesnt exist in the current table create a new entry and return the new code
    int newCode = addNewEntryInLookupTable(table, value);
    return newCode;
}

// Function to create a new entry in the lookup
int addNewEntryInLookupTable(LookupTable *table, const char *value){

    int count = table->count;
    int code = count + 1;
    table->entries = realloc(table->entries, sizeof(LookupEntry) * (count + 1));
    table->entries[count].code = code;
    table->entries[count].value = strdup(value);
    table->count++;

    return code;
}


// Function to initialize the picnic table database
void initializePicnicTable(Database *db, int initialSize) {
    // Allocate memory for the picnicTables array
    db->picnicTableEntry.picnicTables = (PicnicTableData *)malloc(initialSize * sizeof(PicnicTableData));
    if (db->picnicTableEntry.picnicTables == NULL) {
        perror("Error allocating memory for picnic tables");
        exit(1);  // Exit if memory allocation fails
    }

    // Set the initial picnicTable count to 0
    db->picnicTableEntry.count = 0;
}

// Function to cleanup memory when done
void freePicnicTable(Database *db) {
    if (db->picnicTableEntry.picnicTables != NULL) {
        free(db->picnicTableEntry.picnicTables);  // Free the memory allocated for picnic tables
        db->picnicTableEntry.picnicTables = NULL; // Set the pointer to NULL to avoid dangling pointer
    }
}


// Function to read a CSV file and populate the picnicTables array
void importDB(Database *db, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) { return -1; }

    char line[1024];
    int isFirstLine = 1;
    int tableId = 1;

    int picnicTableIndex = 0;

    //Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) 
    {
        //Find the index in the line where the newline is located
        size_t newLineIndex = strcspn(line, "\n");

        //Replace the index of the newline with the null terminator
        line[newLineIndex] = '\0';

        // Parse CSV line
        char *token = strtok(line, ",");
        char* entries[10];
        int entriesCount = 0;

        //Keep iterating through each entry in a line and populate them into the array of entries
        while (token != NULL && entriesCount < 10)
        {
            entries[entriesCount] = token;
            entriesCount++;

            token = strtok(NULL, "");
        }

        //If a line in the file has more than 10 or less than 10 entries then skip it
        if (entriesCount != 10) continue;

        // Add to lookup tables
        int tableTypeCode = findCodeFromLookupTable(&db->tableType, entries[1]);
        int surfaceMaterialCode = findCodeFromLookupTable(&db->surfaceMaterial, entries[2]);
        int structuralMaterialCode = findCodeFromLookupTable(&db->structuralMaterial, entries[3]);
        findCodeFromLookupTable(&db->neighborhood, entries[6]);

        // If the capacity limit has reached resize the picnic table by doubling the capacity
        if (db->picnicTableEntry.count >= db->picnicTableEntry.capacity) 
        {
            db->picnicTableEntry.capacity *= 2;
            db->picnicTableEntry.picnicTables = realloc(db->picnicTableEntry.picnicTables, sizeof(PicnicTableData *) * db->picnicTableEntry.capacity);
        }

        PicnicTable *pt = &db->picnicTableEntry.picnicTables[picnicTableIndex++];

        pt->tableId = tableId++;

        pt->siteId = atoi(entries[0]);

        pt->tableTypeId = tableTypeCode;

        pt->surfaceMaterialId = surfaceMaterialCode;

        pt->structuralMaterialId = structuralMaterialCode;

        strcpy(pt->streetAvenue, entries[4]);

        pt->neighbhdId = atoi(entries[5]);

        //pt->ward = atoi(entries[7] + 5);  // Extract number from "WARD XX"

        strcpy(pt->latitude, entries[8]);

        strcpy(pt->longitude, entries[9]);
    }

    fclose(file);
}

//Function to free
void freeDB(Database *db){

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