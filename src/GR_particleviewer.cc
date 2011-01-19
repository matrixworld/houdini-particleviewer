#include "GR_particleviewer.hh"

int ParticleViewerHook::getWireMask(GU_Detail* /*gdp*/, const GR_DisplayOption *dopt) const
{
	return GEOPRIMALL;
}

void ParticleViewerHook::renderWire(
		GU_Detail *gdp,
		RE_Render &ren,
		const GR_AttribOffset &ptinfo,
		const GR_DisplayOption *dopt,
		float lod,
		const GU_PrimGroupClosure *hidden_geometry
		)
{
	int                  i, nprim, nvtx;
	GEO_Primitive       *prim;
	
	nprim = gdp->primitives().entries();
	for (i = 0; i < nprim; i++)
	{
	    prim = gdp->primitives()(i);
	
	    // Ignore hidden geomtry
	    if (hidden_geometry && hidden_geometry->containsPrim(prim))
	        continue;
	
	    // Only deal with particles
	    if (!(prim->getPrimitiveId() & GEOPRIMPART))
	        continue;

		nvtx = prim->getVertexCount();

		for (int j=0; j < nvtx; j++)
		{
			GEO_Point* point = prim->getVertex(j).getPt();
			UT_Vector4 pos = point->getPos();

			UT_Vector3 scale( 1.0f, 1.0f, 1.0f );
			GEO_AttributeHandle scaleAttr = gdp->getPointAttribute( "scale" );
			if ( scaleAttr.isAttributeValid() )
			{
				scaleAttr.setElement( point );
				scale = scaleAttr.getV3();
			}

			ren.pushMatrix();

			ren.translate( pos.x(), pos.y(), pos.z() );
			ren.scale( scale.x(), scale.y(), scale.z() );

			ren.beginClosedLine();

			ren.vertex3DW( -0.5, -0.5, -0.5 );
			ren.vertex3DW(  0.5, -0.5, -0.5 );
			ren.vertex3DW(  0.5,  0.5, -0.5 );
			ren.vertex3DW( -0.5,  0.5, -0.5 );

			ren.endClosedLine();

			ren.beginClosedLine();

			ren.vertex3DW( -0.5, -0.5, 0.5 );
			ren.vertex3DW(  0.5, -0.5, 0.5 );
			ren.vertex3DW(  0.5,  0.5, 0.5 );
			ren.vertex3DW( -0.5,  0.5, 0.5 );

			ren.endClosedLine();

			ren.beginLines();

			ren.vertex3DW( -0.5, -0.5, -0.5 );
			ren.vertex3DW( -0.5, -0.5,  0.5 );

			ren.vertex3DW(  0.5,  0.5, -0.5 );
			ren.vertex3DW(  0.5,  0.5,  0.5 );

			ren.vertex3DW( -0.5,  0.5, -0.5 );
			ren.vertex3DW( -0.5,  0.5,  0.5 );

			ren.vertex3DW(  0.5, -0.5, -0.5 );
			ren.vertex3DW(  0.5, -0.5,  0.5 );

			ren.endLines();

			ren.popMatrix();
		}

	}
}

int ParticleViewerHook::getShadedMask(GU_Detail* /*gdp*/, const GR_DisplayOption* dopt) const
{
	return GEOPRIMALL;
}

void ParticleViewerHook::renderShaded(
		GU_Detail *gdp,
		RE_Render &ren,
		const GR_AttribOffset &ptinfo,
		const GR_DisplayOption *dopt,
		float lod,
		const GU_PrimGroupClosure *hidden_geometry
		)
{
	int                  i, nprim, nvtx;
	GEO_Primitive       *prim;
	
	nprim = gdp->primitives().entries();
	for (i = 0; i < nprim; i++)
	{
	    prim = gdp->primitives()(i);
	
	    // Ignore hidden geomtry
	    if (hidden_geometry && hidden_geometry->containsPrim(prim))
	        continue;
	
	    // Only deal with particles
	    if (!(prim->getPrimitiveId() & GEOPRIMPART))
	        continue;

		nvtx = prim->getVertexCount();

		for (int j=0; j < nvtx; j++)
		{
			GEO_Point* point = prim->getVertex(j).getPt();
			UT_Vector4 pos = point->getPos();
			
			UT_Vector3 cd( 1.0f, 1.0f, 1.0f );
			GEO_AttributeHandle colorAttr = gdp->getPointAttribute( "Cd" );
			if ( colorAttr.isAttributeValid() )
			{
				colorAttr.setElement( point );
				cd = colorAttr.getV3();
			}

			UT_Vector3 scale( 1.0f, 1.0f, 1.0f );
			GEO_AttributeHandle scaleAttr = gdp->getPointAttribute( "scale" );
			if ( scaleAttr.isAttributeValid() )
			{
				scaleAttr.setElement( point );
				scale = scaleAttr.getV3();
			}

			ren.setColor( cd.x(), cd.y(), cd.z(), 1.0 );

			ren.pushMatrix();

			ren.translate( pos.x(), pos.y(), pos.z() );

			ren.scale( scale.x(), scale.y(), scale.z() );

			ren.beginQuads();

			float nml[3];
			nml[0] = 0.0; nml[1] = 0.0; nml[2] = -1.0;
			ren.n3DW(nml);
			
			ren.vertex3DW( -0.5,  0.5, -0.5 );
			ren.vertex3DW(  0.5,  0.5, -0.5 );
			ren.vertex3DW(  0.5, -0.5, -0.5 );
			ren.vertex3DW( -0.5, -0.5, -0.5 );

			nml[0] = 0.0; nml[1] = 0.0; nml[2] = 1.0; 
			ren.n3DW(nml);

			ren.vertex3DW( -0.5, -0.5,  0.5 );
			ren.vertex3DW(  0.5, -0.5,  0.5 );
			ren.vertex3DW(  0.5,  0.5,  0.5 );
			ren.vertex3DW( -0.5,  0.5,  0.5 );

			nml[0] = 0.0; nml[1] = -1.0; nml[2] = 0.0;
			ren.n3DW(nml);
			
			ren.vertex3DW( -0.5, -0.5, -0.5 );
			ren.vertex3DW(  0.5, -0.5, -0.5 );
			ren.vertex3DW(  0.5, -0.5,  0.5 );
			ren.vertex3DW( -0.5, -0.5,  0.5 );

			nml[0] = 0.0; nml[1] = 1.0; nml[2] = 0.0;
			ren.n3DW(nml);

			ren.vertex3DW( -0.5,  0.5,  0.5 );
			ren.vertex3DW(  0.5,  0.5,  0.5 );
			ren.vertex3DW(  0.5,  0.5, -0.5 );
			ren.vertex3DW( -0.5,  0.5, -0.5 );

			nml[0] = -1.0; nml[1] = 0.0; nml[2] = 0.0;
			ren.n3DW(nml);

			ren.vertex3DW( -0.5, -0.5,  0.5 );
			ren.vertex3DW( -0.5,  0.5,  0.5 );
			ren.vertex3DW( -0.5,  0.5, -0.5 );
			ren.vertex3DW( -0.5, -0.5, -0.5 );

			nml[0] = 1.0; nml[1] = 0.0; nml[2] = 0.0;
			ren.n3DW(nml);

			ren.vertex3DW(  0.5,  0.5, -0.5 );
			ren.vertex3DW(  0.5,  0.5,  0.5 );
			ren.vertex3DW(  0.5, -0.5,  0.5 );
			ren.vertex3DW(  0.5, -0.5, -0.5 );

			ren.endQuadStrip();

			ren.popMatrix();
		}

	}
}



void
newRenderHook(GR_RenderTable *table)
{
	std::cout << std::endl << "Loading Particle Box" << std::endl;
	table->addHook( new ParticleViewerHook, GR_RENDER_HOOK_VERSION );
}

