/*
 * Wazuh Module for OpenSCAP
 * Wazuh Inc.
 * April 25, 2016
 */

#ifndef WM_OSCAP
#define WM_OSCAP

#define WM_DEF_TIMEOUT      120     // Default runtime limit (2 minutes)
#define WM_DEF_INTERVAL     86400   // Default cycle interval (1 day)

#define WM_OSCAP_LOGTAG ARGV0 ":oscap"

typedef struct wm_oscap_profile {
    char *name;                     // Profile name (string)
    struct wm_oscap_profile *next;  // Pointer to next
} wm_oscap_profile;

typedef union wm_oscap_flags {
    struct {
        unsigned int skip_result_pass:1;
        unsigned int skip_result_fail:1;
        unsigned int skip_result_notchecked:1;
        unsigned int skip_result_notapplicable:1;

        unsigned int skip_severity_low:1;
        unsigned int skip_severity_medium:1;
        unsigned int skip_severity_high:1;

        unsigned int custom_result_flags:1;
        unsigned int custom_severity_flags:1;
        unsigned int error:1;
    };

    struct {
        unsigned int skip_result:4;
        unsigned int skip_severity:3;
    };
} wm_oscap_flags;

typedef struct wm_oscap_file {
    char *name;                     // Profile name (string)
    wm_oscap_profile *profiles;     // Profiles (linked list)
    wm_oscap_flags flags;           // Flags
    unsigned int timeout;           // Execution time limit (seconds)
    struct wm_oscap_file *next;     // Pointer to next
} wm_oscap_file;

typedef struct wm_oscap {
    unsigned int interval;          // Default ime interval between cycles
    unsigned int timeout;           // Default execution time limit (seconds)
    wm_oscap_flags flags;           // Default flags
    wm_oscap_file *files;           // Files (linked list)
} wm_oscap;

extern const wm_context WM_OSCAP_CONTEXT;   // Context

// Parse XML
int wm_oscap_read(const OS_XML *xml, xml_node **nodes, wmodule *module);

#endif // WM_OSCAP
