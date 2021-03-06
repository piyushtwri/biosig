/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "FEF-IntermediateDraft"
 * 	found in "../annexb-snacc-122001.asn1"
 */

#ifndef	_LimitSpecEntry_H_
#define	_LimitSpecEntry_H_


#include <asn_application.h>

/* Including external dependencies */
#include "HandleRef.h"
#include "MetricsCode.h"
#include "UnitCode.h"
#include "CurLimAlStat.h"
#include "AbsoluteRange.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* LimitSpecEntry */
typedef struct LimitSpecEntry {
	HandleRef_t	 sectionhandle;
	MetricsCode_t	 alsourceid;
	UnitCode_t	 unitcode;
	CurLimAlStat_t	 limalstat;
	AbsoluteRange_t	 limalval;
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} LimitSpecEntry_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_LimitSpecEntry;

#ifdef __cplusplus
}
#endif

#endif	/* _LimitSpecEntry_H_ */
