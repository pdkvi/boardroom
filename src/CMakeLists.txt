add_executable(boardroom
	"main.cpp"

	"MainWindow.hpp"
	"MainWindow.cpp"
	"MainWindow.ui"

	"FreeHandDrawingItem.hpp"
	"FreeHandDrawingItem.cpp"

	"WhiteboardScene.hpp"
	"WhiteboardScene.cpp"

	"WhiteboardView.hpp"
	"WhiteboardView.cpp"
)

set_target_properties(boardroom PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO

	WIN32_EXECUTABLE YES
	MACOSX_BUNDLE YES
)

target_link_libraries(boardroom PRIVATE Qt::Core Qt::Gui Qt::Widgets)