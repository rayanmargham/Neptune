#ifndef _NEPTUNE_ACPI_H_
#define _NEPTUNE_ACPI_H_
void acpi_init();
void *GetTable(char* signature, size_t index);
#endif