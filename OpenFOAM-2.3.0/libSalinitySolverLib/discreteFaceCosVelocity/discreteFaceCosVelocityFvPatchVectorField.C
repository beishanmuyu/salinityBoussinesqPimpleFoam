/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "discreteFaceCosVelocityFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::discreteFaceCosVelocityFvPatchVectorField::discreteFaceCosVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    mixedFvPatchVectorField(p, iF),
    nIntervals_(10),
    A_(0.0, 0.0, 0.0),
    H_(1.0),
    Hdirection_(0.0, 0.0, 0.0),
    omega0_(0.0),
    phi0_(0.0),
    minZ_(0.0)
{
    this->refValue() = pTraits<vector>::zero;
    this->refGrad() = pTraits<vector>::zero;
    this->valueFraction() = 0.0;
    this->setPatchVelocities(this->refValue());
    
    Info << "Executing discreteFaceCosVelocityFvPatchVectorField(fvPatch, DimensionedField) " << endl;
}


Foam::discreteFaceCosVelocityFvPatchVectorField::discreteFaceCosVelocityFvPatchVectorField
(
    const discreteFaceCosVelocityFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    mixedFvPatchField<vector>(ptf, p, iF, mapper),
    nIntervals_(ptf.nIntervals_),
    A_(ptf.A_),
    H_(ptf.H_),
    Hdirection_(ptf.Hdirection_),
    omega0_(ptf.omega0_),
    phi0_(ptf.phi0_),
    minZ_(ptf.minZ_)
{
    this->setPatchVelocities(this->refValue());
    mixedFvPatchVectorField::updateCoeffs();

    Info << "Executing discreteFaceCosVelocityFvPatchVectorField(discreteFaceCosVelocity, fvPatch, DimensionedField, fvPatchFieldMapper) " << endl;
}


Foam::discreteFaceCosVelocityFvPatchVectorField::discreteFaceCosVelocityFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    mixedFvPatchField<vector>(p, iF)
{
    
    dict.lookup("nIntervals") >> nIntervals_;
    dict.lookup("A") >> A_;
    dict.lookup("H") >> H_;
    dict.lookup("Hdirection") >> Hdirection_;
    dict.lookup("omega0") >> omega0_;
    dict.lookup("phi0") >> phi0_;
    dict.lookup("minZ") >> minZ_;

    if (dict.found("value"))
    {
        fvPatchField<vector>::operator=
        (
            Field<vector>("value", dict, p.size())
        );
    }
    else
    {
        fvPatchField<vector>::operator=(this->patchInternalField());
    }

    this->refValue() = pTraits<vector>::zero;
    this->refGrad() = pTraits<vector>::zero;
    this->valueFraction() = 1.0;
    this->setPatchVelocities(this->refValue());
    mixedFvPatchVectorField::updateCoeffs();

    Info << "Executing discreteFaceCosVelocityFvPatchVectorField(fvPatch, DimensionedField, dictionary) " << endl;
}


Foam::discreteFaceCosVelocityFvPatchVectorField::discreteFaceCosVelocityFvPatchVectorField
(
    const discreteFaceCosVelocityFvPatchVectorField& ptpsf
)
:
    mixedFvPatchVectorField(ptpsf),
    nIntervals_(ptpsf.nIntervals_),
    A_(ptpsf.A_),
    H_(ptpsf.H_),
    Hdirection_(ptpsf.Hdirection_),
    omega0_(ptpsf.omega0_),
    phi0_(ptpsf.phi0_),
    minZ_(ptpsf.minZ_)
{
    this->setPatchVelocities(this->refValue());
    Info << "Executing discreteFaceCosVelocityFvPatchVectorField(const discreteFaceCosVelocity&) " << endl;
}


Foam::discreteFaceCosVelocityFvPatchVectorField::discreteFaceCosVelocityFvPatchVectorField
(
    const discreteFaceCosVelocityFvPatchVectorField& ptpsf,
    const DimensionedField<vector, volMesh>& iF
)
:
    mixedFvPatchVectorField(ptpsf, iF),
    nIntervals_(ptpsf.nIntervals_),
    A_(ptpsf.A_),
    H_(ptpsf.H_),
    Hdirection_(ptpsf.Hdirection_),
    omega0_(ptpsf.omega0_),
    phi0_(ptpsf.phi0_),
    minZ_(ptpsf.minZ_)
{
    this->setPatchVelocities(this->refValue());

    Info << "Executing discreteFaceCosVelocityFvPatchVectorField(const discreteFaceCosVelocity, const DimensionedField) " << endl;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::discreteFaceCosVelocityFvPatchVectorField::autoMap(const fvPatchFieldMapper& m)
{
    mixedFvPatchField<vector>::autoMap(m);

    Info << "Executing autoMap " << endl;
}

void Foam::discreteFaceCosVelocityFvPatchVectorField::rmap(const fvPatchVectorField& pf, const labelList& ll)
{
    mixedFvPatchField<vector>::rmap(pf, ll);
    Info << "Executing rmap " << endl;
}

Foam::label Foam::discreteFaceCosVelocityFvPatchVectorField::whichInterval (scalar zfc)
{
    label iId = -1;
    scalar dz = H_ / scalar(nIntervals_);
    
    for (label i=0; i < nIntervals_; i++)
    {
	scalar iStart = scalar(i) * dz;
	scalar iEnd   = scalar(i+1) * dz;
	if ( (zfc > iStart) && (zfc < iEnd) )
	{
	    iId = i;
	    break;
	}
    }
    
    return iId;
}

void Foam::discreteFaceCosVelocityFvPatchVectorField::setPatchVelocities (vectorField& pV)
{
    scalarField zf = (this->patch().Cf() & Hdirection_) - minZ_;
    scalar t = this->patch().boundaryMesh().mesh().time().value();
    scalar dz = H_ / scalar(nIntervals_);
    
    forAll(pV, iFace)
    {
	label iId = this->whichInterval(zf[iFace]);
	this->refGrad()[iFace] = vector (0.0, 0.0, 0.0);
	if (iId >= 0)
	{
	    scalar iStart = scalar(iId) * dz;
	    scalar iEnd   = scalar(iId+1) * dz;
	    scalar iStartVal = cos(Foam::constant::mathematical::pi * iStart / H_) * (-omega0_) * sin(omega0_ * t + phi0_);
	    scalar iEndVal   = cos(Foam::constant::mathematical::pi * iEnd / H_) * (-omega0_) * sin(omega0_ * t + phi0_);
	    scalar iAvrVal   = 0.5*(iStartVal + iEndVal);
	    this->valueFraction()[iFace] = 1.0;
	    pV[iFace] = A_ * iAvrVal;
	}
	else
	{
	    pV[iFace] = A_*0.0;
	    this->valueFraction()[iFace] = 0.0;
	}
    }
}

void Foam::discreteFaceCosVelocityFvPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }
    
    this->setPatchVelocities(this->refValue());
    
    Info << "max/min velocity: " << gMax(this->refValue()) << "/" << gMin(this->refValue()) << endl;

    mixedFvPatchField<vector>::updateCoeffs();
}


void Foam::discreteFaceCosVelocityFvPatchVectorField::write(Ostream& os) const
{

    mixedFvPatchVectorField::write(os);

    os.writeKeyword("nIntervals") << nIntervals_ << token::END_STATEMENT << nl;

    os.writeKeyword("A") << A_ << token::END_STATEMENT << nl;
        
    os.writeKeyword("H") << H_ << token::END_STATEMENT << nl;
    
    os.writeKeyword("minZ") << minZ_ << token::END_STATEMENT << nl;
    
    os.writeKeyword("Hdirection") << Hdirection_ << token::END_STATEMENT << nl;
    
    os.writeKeyword("omega0") << omega0_ << token::END_STATEMENT << nl;
    
    os.writeKeyword("phi0") << phi0_ << token::END_STATEMENT << nl;
    
}

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        discreteFaceCosVelocityFvPatchVectorField
    );
}



// ************************************************************************* //
