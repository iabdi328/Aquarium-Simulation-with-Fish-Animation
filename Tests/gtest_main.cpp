#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filefn.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

  //  wxInitialize();
    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    auto result = RUN_ALL_TESTS();

  //  wxUninitialize();
    return result;
}