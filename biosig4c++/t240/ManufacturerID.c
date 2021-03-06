/*
 * Generated by asn1c-0.9.21 (http://lionet.info/asn1c)
 * From ASN.1 module "FEF-IntermediateDraft"
 * 	found in "../annexb-snacc-122001.asn1"
 */

#include <asn_internal.h>

#include "ManufacturerID.h"

static int
memb_uuid_constraint_1(asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	const OCTET_STRING_t *st = (const OCTET_STRING_t *)sptr;
	size_t size;
	
	if(!sptr) {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	size = st->size;
	
	if((size == 16)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		_ASN_CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_TYPE_member_t asn_MBR_ManufacturerID_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ManufacturerID, choice.oid),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OBJECT_IDENTIFIER,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"oid"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ManufacturerID, choice.uuid),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_OCTET_STRING,
		memb_uuid_constraint_1,
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"uuid"
		},
};
static asn_TYPE_tag2member_t asn_MAP_ManufacturerID_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 0, 0, 0 }, /* oid at 142 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 1, 0, 0 } /* uuid at 145 */
};
static asn_CHOICE_specifics_t asn_SPC_ManufacturerID_specs_1 = {
	sizeof(struct ManufacturerID),
	offsetof(struct ManufacturerID, _asn_ctx),
	offsetof(struct ManufacturerID, present),
	sizeof(((struct ManufacturerID *)0)->present),
	asn_MAP_ManufacturerID_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ManufacturerID = {
	"ManufacturerID",
	"ManufacturerID",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	0,	/* No PER visible constraints */
	asn_MBR_ManufacturerID_1,
	2,	/* Elements count */
	&asn_SPC_ManufacturerID_specs_1	/* Additional specs */
};

