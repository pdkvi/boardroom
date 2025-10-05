add_subdirectory("Core")
add_subdirectory("Shapes")

target_sources(boardroom PRIVATE
	"FreeDrawingItem.hpp"
	"FreeDrawingItem.cpp"
)