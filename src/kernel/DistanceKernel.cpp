/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007 Christian Gehl
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "lib/config.h"

#include "lib/common.h"
#include "lib/io.h"
#include "kernel/DistanceKernel.h"
#include "features/RealFeatures.h"

CDistanceKernel::CDistanceKernel(INT size, DREAL w ,CDistance* d)
: CKernel(size), distance(d), width(w)
{
	ASSERT(distance);
	SG_REF(distance);
}

CDistanceKernel::CDistanceKernel(
	CFeatures *l, CFeatures *r, DREAL w , CDistance* d)
: CKernel(10), distance(d), width(w)
{
	ASSERT(distance);
	SG_REF(distance);
	init(l, r);
}

CDistanceKernel::~CDistanceKernel()
{
	// important to have the cleanup of CKernel first, it calls get_name which
	// uses the distance
	cleanup();
	SG_UNREF(distance);
}

bool CDistanceKernel::init(CFeatures* l, CFeatures* r)
{
	ASSERT(distance);
	return CKernel::init(l,r) && distance->init(l,r);
}

DREAL CDistanceKernel::compute(INT idx_a, INT idx_b)
{
	DREAL result=distance->distance(idx_a, idx_b);
	return exp(-result/width);
}

bool CDistanceKernel::load_init(FILE* src)
{
	return false;
}

bool CDistanceKernel::save_init(FILE* dest)
{
	return false;
}
