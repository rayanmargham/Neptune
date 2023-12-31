#include "kheap.h"
#include "pmm.h"
#include "memfunc.h"
#include "limine.h"
#include "flanterm/flanterm.h"
#include "flanterm/backends/fb.h"
#include "limine.h"
#include "lai/core.h"
#include "lai/helpers/sci.h"
#include "lai/helpers/pm.h"
#include "lai/drivers/ec.h"
#include "lai/helpers/pc-bios.h"
#include "kpanic.h"
extern struct flanterm_context *ft_ctx;
extern void kflantprint(struct flanterm_context *ft_ctx, char msg[], size_t count, uint32_t color, char from_who[], size_t length_for_that, bool next_line);
volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 1
};
struct acpi_xsdt_t *xsdt;

void *scandatable(const char* signaturem, size_t index)
{
    int makingsure = 0;
    int amount_of_entries = (xsdt->header.length - sizeof(acpi_header_t)) / sizeof(uint64_t);
    for (int i = 0; i < amount_of_entries; i++)
    {
        struct acpi_header_t *gamer_table = laihost_map(xsdt->tables[i], 0);
        if (!memcmp(signaturem, gamer_table->signature, 4))
        {
            if (index == makingsure)
            {
                return gamer_table;
            }
            else
            {
                makingsure++;
            }
        }
    }
    return NULL;
}
void *GetTable(const char* signature, size_t index)
{
    if (!memcmp(signature, "DSDT", 4))
    {
        struct acpi_fadt_t *fadt_among_us = scandatable("FACP", 0);

        return laihost_map(fadt_among_us->x_dsdt, 0);
    }
    else
    {
        return scandatable(signature, index);
    }
}
void acpi_init()
{
    uint64_t rsdp_address = rsdp_request.response->address;
    
    struct acpi_rsdp_t *rsdptmp = (struct acpi_rsdp_t*)rsdp_address;

    if (rsdptmp->revision == 2)
    {
        struct acpi_xsdp_t *crazy = (struct acpi_xsdp_t*)rsdp_address;
        xsdt = laihost_map((struct acpi_xsdt_t*)crazy->xsdt, 0);
        lai_enable_tracing(LAI_TRACE_IO);
        lai_set_acpi_revision(xsdt->header.revision);

        lai_create_namespace();
        kflantprint(ft_ctx, "ACPI Loaded!", 13, 0xFFC0CB, "ACPI", 5, true);
        
    }
    else
    {
        kpanic("go back to the 90s kid :hahaha:");
    }
}