add_executable(boardroom)

add_subdirectory("Commands")
add_subdirectory("Items")
add_subdirectory("Tools")
add_subdirectory("Utility")
add_subdirectory("Widgets")

target_sources(boardroom PRIVATE
	"main.cpp"

	"MainWindow.hpp"
	"MainWindow.cpp"
	"MainWindow.ui"

	"WhiteboardScene.hpp"
	"WhiteboardScene.cpp"

	"WhiteboardToolsModel.hpp"
	"WhiteboardToolsModel.cpp"
)

set_target_properties(boardroom PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO

	WIN32_EXECUTABLE YES
	MACOSX_BUNDLE YES
)

target_include_directories(boardroom PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(boardroom PRIVATE Qt::Core Qt::Gui Qt::Widgets)