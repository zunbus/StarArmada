// © 2026 Hubert Filas. All Rights Reserved.

#include "FreighterMeshSet.h"

UFreighterMeshSet::UFreighterMeshSet()
{
    // Initialize category map with expected keys
    Categories.Add("Hangars", FFreighterCategory());
    Categories.Add("Bows", FFreighterCategory());
    Categories.Add("CargoPodsPortside", FFreighterCategory());
    Categories.Add("CargoPodsStarboard", FFreighterCategory());
    Categories.Add("Thrusters", FFreighterCategory());
    Categories.Add("Other", FFreighterCategory());

    // Initialize variants for each category
    Categories["Hangars"].Variants.Add("Innovative", FFreighterVariant());
    Categories["Hangars"].Variants.Add("Classic", FFreighterVariant());
    Categories["Hangars"].Variants.Add("SkyView", FFreighterVariant());

    Categories["Bows"].Variants.Add("Storage", FFreighterVariant());
    Categories["Bows"].Variants.Add("Terraformator", FFreighterVariant());

    Categories["CargoPodsPortside"].Variants.Add("Small", FFreighterVariant());
    Categories["CargoPodsPortside"].Variants.Add("Medium", FFreighterVariant());
    Categories["CargoPodsPortside"].Variants.Add("Large", FFreighterVariant());

    Categories["CargoPodsStarboard"].Variants.Add("Small", FFreighterVariant());
    Categories["CargoPodsStarboard"].Variants.Add("Medium", FFreighterVariant());
    Categories["CargoPodsStarboard"].Variants.Add("Large", FFreighterVariant());

    Categories["Thrusters"].Variants.Add("Efficient", FFreighterVariant());
    Categories["Thrusters"].Variants.Add("Balanced", FFreighterVariant());
    Categories["Thrusters"].Variants.Add("Powerful", FFreighterVariant());

    Categories["Other"].Variants.Add("CommStation", FFreighterVariant());
    Categories["Other"].Variants.Add("PCD", FFreighterVariant());
    Categories["Other"].Variants.Add("Reactor1", FFreighterVariant());
    Categories["Other"].Variants.Add("Reactor2", FFreighterVariant());
    Categories["Other"].Variants.Add("PCD-Cover", FFreighterVariant());
    Categories["Other"].Variants.Add("Reactor1-Cover", FFreighterVariant());
    Categories["Other"].Variants.Add("Reactor2-Cover", FFreighterVariant());
}
