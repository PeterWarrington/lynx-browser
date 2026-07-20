/*
 * $LynxId: structdump.h,v 1.16 2026/05/18 23:21:16 tom Exp $
 * Some macros to dump out formatted struct's via the trace file.  -KED
 *
 */
#ifndef STRUCTDUMP_H
#define STRUCTDUMP_H

#include <HTForms.h>

#if defined(USE_COLOR_STYLE)
#define if_USE_COLOR_STYLE(stmt) stmt
#else
#define if_USE_COLOR_STYLE(stmt)	/* nothing */
#endif

#define ConCat(a,b) a b
#define FieldFormat(fmt) ConCat(ConCat("%20s:", fmt), "\n")

#define DumpAddress(base, field) \
	    CTRACE((tfp, FieldFormat("%p"), #field, (base)->field))

#define DumpBoolean(base, field) \
	    CTRACE((tfp, FieldFormat("%s"), #field, (base)->field ? "true" : "false"))

#define DumpNumber(base, field) \
	    CTRACE((tfp, FieldFormat("%d"), #field, (base)->field)) \

#define DumpString(base, field) \
	    if ((base)->field != NULL) { \
		CTRACE((tfp, FieldFormat("|%s|"), #field, (base)->field)); \
	    } else { \
		CTRACE((tfp, FieldFormat("<NULL>"), #field)); \
	    }

#define ShowLinkType(type) \
	    ((type) == INPUT_ANCHOR \
	    ? "INPUT_ANCHOR" \
	    : ((type) == HYPERTEXT_ANCHOR \
	       ? "HYPERTEXT_ANCHOR" \
	       : ((type) == INTERNAL_LINK_ANCHOR \
		   ? "INTERNAL_ANCHOR" \
		   : ((type) & HYPERTEXT_ANCHOR \
		      ? "EXTERNAL?" \
		      : ((type) & INTERNAL_LINK_ANCHOR \
		         ? "INTERNAL?" \
		         : "?")))))

#define DumpLinkType(base, field) \
	CTRACE((tfp, FieldFormat("%s"), #field, ShowLinkType((base)->field)))

/* usage: DUMPSTRUCT_LINK(link_ptr, "message"); */
#define   DUMPSTRUCT_LINK(L,X) \
	do { \
	    CTRACE((tfp, "DUMP: link_ptr=%p  sizeof=%lu  ["X"]\n", \
		   (L), sizeof(*(L)))); \
	    if ((L)) { \
		CTRACE((tfp, "LinkInfo struct {\n")); \
		DumpAddress(L, lname); \
		DumpString(L, lname); \
		DumpString(L, l_hightext); \
		DumpBoolean(L, inUnderline); \
		DumpNumber(L, lx); \
		DumpNumber(L, ly); \
		DumpNumber(L, type); \
		DumpNumber(L, anchor_number); \
		DumpNumber(L, anchor_line_num); \
		/* HiliteList list */ \
		DumpAddress(L, l_form); \
		DumpString(L, submit_action); \
		CTRACE((tfp, "}\n")); \
	    } \
	    CTRACE_FLUSH(tfp); \
	} while (0)

/* usage: DUMPSTRUCT_ANCHOR(anchor_ptr, "message"); */
#define   DUMPSTRUCT_ANCHOR(A,X) \
	do { \
	    CTRACE((tfp, "DUMP: anchor_ptr=%p  sizeof=%lu  ["X"]\n", \
		   (A), sizeof(*(A)))); \
	    if ((A)) { \
		CTRACE((tfp, "TextAnchor struct {\n" )); \
		DumpAddress(A, next); \
		DumpAddress(A, prev); \
		DumpNumber(A, sgml_offset); \
		DumpNumber(A, number); \
		DumpNumber(A, show_number); \
		DumpNumber(A, line_num); \
		DumpNumber(A, line_pos); \
		DumpNumber(A, extent); \
		DumpBoolean(A, show_anchor); \
		DumpBoolean(A, inUnderline); \
		DumpBoolean(A, expansion_anch); \
		DumpLinkType(A, link_type); \
		DumpAddress(A, input_field); \
		if (A->input_field != NULL) { \
		    DumpString(A, input_field->name); \
		} \
		/* HiliteList lites */ \
		DumpAddress(A, anchor); \
		CTRACE((tfp, "}\n")); \
	    } \
	    CTRACE_FLUSH(tfp); \
	} while (0)

/* usage: DUMPSTRUCT_FormInfo(forminfo_ptr, "message"); */
#define   DUMPSTRUCT_FormInfo(F,X) \
	do { \
	    CTRACE((tfp, "DUMP: forminfo_ptr=%p  sizeof=%lu  ["X"]\n", \
		   (F), sizeof(*(F)))); \
	    if ((F)) { \
		CTRACE((tfp, "FormInfo struct {\n")); \
		DumpAddress(F, name); \
		DumpString(F, name); \
		DumpNumber(F, number); \
		CTRACE((tfp, FieldFormat("%s"), "type", ShowFieldType((F)->type))); \
		DumpAddress(F, value); \
		DumpString(F, value); \
		DumpAddress(F, orig_value); \
		DumpString(F, orig_value); \
		DumpNumber(F, size); \
		DumpNumber(F, maxlength); \
		DumpNumber(F, group); \
		DumpNumber(F, num_value); \
		DumpNumber(F, hrange); \
		DumpNumber(F, lrange); \
		DumpAddress(F, select_list); \
		DumpString(F, submit_action); \
		DumpNumber(F, submit_method); \
		DumpString(F, submit_enctype); \
		DumpString(F, submit_title); \
		DumpNumber(F, no_cache); \
		DumpString(F, cp_submit_value); \
		DumpString(F, orig_submit_value); \
		DumpNumber(F, size_l); \
		DumpNumber(F, disabled); \
		DumpNumber(F, readonly); \
		DumpNumber(F, name_cs); \
		DumpNumber(F, disabled); \
		DumpNumber(F, readonly); \
		DumpNumber(F, name_cs); \
		DumpNumber(F, name_cs); \
		DumpNumber(F, value_cs); \
		DumpString(F, accept_cs); \
		CTRACE((tfp, "}\n")); \
	    } \
	    CTRACE_FLUSH(tfp); \
	} while (0)

/* usage: DUMPSTRUCT_InputFieldData(inputfield_ptr, "message"); */
#define   DUMPSTRUCT_InputFieldData(I,X) \
	do { \
	    CTRACE((tfp, "DUMP: inputdata_ptr=%p  sizeof=%lu  ["X"]\n", \
		   (I), sizeof(*(I)))); \
	    if ((I)) { \
		CTRACE((tfp, "InputFieldData struct {")); \
		DumpString(I, accept); \
		DumpString(I, align); \
		DumpBoolean(I, checked); \
		DumpString(I, iclass); \
		DumpBoolean(I, disabled); \
		DumpBoolean(I, readonly); \
		DumpString(I, error); \
		DumpString(I, height); \
		DumpString(I, id); \
		DumpString(I, lang); \
		DumpString(I, max); \
		DumpString(I, maxlength); \
		DumpString(I, md); \
		DumpString(I, min); \
		DumpString(I, name); \
		DumpNumber(I, size); \
		DumpString(I, src); \
		DumpString(I, type); \
		DumpString(I, value); \
		DumpString(I, width); \
		DumpNumber(I, name_cs); \
		DumpString(I, value); \
		DumpString(I, accept_cs); \
		DumpString(I, accept_cs); \
		DumpString(I, submit_action); \
		CTRACE((tfp, "}\n")); \
	    } \
	    CTRACE_FLUSH(tfp); \
	} while (0)

/* usage: DUMPSTRUCT_LINE(htline_ptr, "message"); */
#define   DUMPSTRUCT_LINE(L,X) \
	do { \
	    CTRACE((tfp, "DUMP: htline_ptr=%p  sizeof=%lu  ["X"]\n", \
		   (L), sizeof(*(L)))); \
	    if ((L)) { \
		CTRACE((tfp, "HTLine struct {")); \
		DumpAddress(L, next); \
		DumpAddress(L, prev); \
		DumpNumber(L, offset); \
		DumpNumber(L, size); \
		DumpAddress(L, data); \
		DumpString(L, data); \
		if_USE_COLOR_STYLE(DumpAddress(L, styles)); \
		if_USE_COLOR_STYLE(DumpNumber(L, numstyles)); \
		CTRACE((tfp, "}\n")); \
	    } \
	    CTRACE_FLUSH(tfp); \
	} while (0)

#endif /* STRUCTDUMP_H */
