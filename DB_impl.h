/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 * 
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: <TODO: Group Member Names>
 * Lab instructor: <TODO: Your lab instructor's name here>
 * Lecture instructor: <TODO: Your lecture instructor's name here>
 */


#ifndef DB_IMPL_H
#define DB_IMPL_H

typedef struct {
    int tableId;
    int siteId;
    int tableTypeId;           // Table type, e.g., "Picnic Table"
    int surfaceMaterialId;     // Surface material, e.g., "Wood"
    int structuralMaterialId;  // Structural material, e.g., "Steel"
    char streetAvenue[50];        // Street/Avenue
    int neighbhdId;               // Neighbourhood Id
    int ward;                     // Ward number
    char latitude[50];            // Latitude as string
    char longitude[50];           // Longitude as string
} PicnicTable;

typedef struct {
    PicnicTable* picnicTables;
    int count;
    int capacity;
} PicnicTableData;

// Struct for the main database structure that holds picnic table data
typedef struct {
    PicnicTableData picnicTableEntry;  
    LookupTable tableType;
    LookupTable surfaceMaterial;
    LookupTable structuralMaterial;
    LookupTable neighborhood; 
} Database;

#endif