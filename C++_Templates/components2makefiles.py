#!/usr/bin/python
from typing import TypedDict, List
import os
from pathlib import Path


class SourceDirectoryNode(TypedDict):
    directory_name: str
    source_files: List[Path]
    subdirectories: List[dict]


class MakefileIncludeDirectoryNode(TypedDict):
    directory_name: str
    include_file: Path
    subdirectories: List[dict]


class MakefileGenerator():
    def __init__(self):
        self._code_base_directory = None
        self._makefile_base_directory = None
        self._source_directory_structure = None
        self._makefile_structure = None

    def generate_make_include_files(self, code_base_directory: Path, makefile_base_directory: Path):
        self._code_base_directory = code_base_directory
        self._makefile_base_directory = makefile_base_directory
        self._source_directory_structure = self._derive_source_code_structure_from_directory(self._code_base_directory)
        self._makefile_structure = self._create_make_include_files_for_node(self._source_directory_structure)
        self._write_global_include_file()

    def _derive_source_code_structure_from_directory(self, source_path: Path) -> SourceDirectoryNode:
        return_node: SourceDirectoryNode = {"directory_name": str(source_path.stem),
                                            "source_files":   sorted(source_path.glob("*.cpp")),
                                            "subdirectories": [self._derive_source_code_structure_from_directory(subdir) for subdir in source_path.iterdir() if subdir.is_dir()]}

        return return_node

    def _create_make_include_files_for_node(self, source_directory_node: SourceDirectoryNode) -> MakefileIncludeDirectoryNode:
        directory_node = {'directory_name': source_directory_node['directory_name'],
                          'include_file':   Path(),
                          'subdirectories': []}


        relative_source_path = Path()
        include_file_path = Path()

        source_lines = ["CXX_SRCS += \\"]
        object_lines = ["USER_OBJS += \\"]
        dependency_lines = [" CXX_DEPS += \\"]

        for source_file in source_directory_node['source_files']:
            relative_source_path = source_file.relative_to(self._makefile_base_directory)
            include_file_path = self._makefile_base_directory / relative_source_path.parent / Path("subdir.mk")
            source_lines.append("    $(SRCD)/{} \\".format(str(source_file.name)))
            object_lines.append("    $(SRCD)/{} \\".format(str(source_file.with_suffix('.o').name)))
            dependency_lines.append("    $(SRCD)/{} \\".format(str(source_file.with_suffix('.d').name)))

        if len(source_lines) > 0:
            source_lines[-1] = source_lines[-1].replace("\\", "")

        if len(object_lines) > 0:
            object_lines[-1] = object_lines[-1].replace("\\", "")

        if len(dependency_lines) > 0:
            dependency_lines[-1] = dependency_lines[-1].replace("\\", "")

        source_directory_line = "SRCD = $(PROJECT_DIR)/{}\n".format(str(relative_source_path.parent))


        if include_file_path != Path():
            print("Writing makefile {}".format(str(include_file_path)))
            with open(include_file_path, 'w') as include_file:
                include_file.write("{}\n\n".format(source_directory_line))
                for line in source_lines:
                    include_file.write("{}\n".format(line))
                include_file.write("\n")
                for line in object_lines:
                    include_file.write("{}\n".format(line))
                include_file.write("\n")
                for line in dependency_lines:
                    include_file.write("{}\n".format(line))
                include_file.write("\n")

            directory_node['include_file'] = include_file_path

        for subdir_node in source_directory_node['subdirectories']:
            directory_node['subdirectories'].append(self._create_make_include_files_for_node(subdir_node))

        return directory_node

    def _create_include_lines_for_node(self, node: MakefileIncludeDirectoryNode) -> List[str]:
        include_lines = []
        if node['include_file'] != Path():
            relative_path_to_subdir_mk = node['include_file'].relative_to(self._makefile_base_directory)
            include_lines.append("-include ./{}".format(str(relative_path_to_subdir_mk)))
        for subdirectory in node['subdirectories']:
            include_lines.extend(self._create_include_lines_for_node(subdirectory))
        return include_lines

    def _write_global_include_file(self):
        if self._code_base_directory:
            global_include_file_path = self._code_base_directory / Path("all_subdirs.mk")
            include_lines = self._create_include_lines_for_node(self._makefile_structure)
            with open(global_include_file_path, 'w') as include_file:
                for line in include_lines:
                    include_file.write("{}\n".format(line))


if __name__ == '__main__':
    print("Make include file generator started...")
    code_base_dir = (Path(__file__).parent / "Components").resolve()
    makefile_base_dir = Path(__file__).parent.resolve()
    generator = MakefileGenerator()
    generator.generate_make_include_files(code_base_dir, makefile_base_dir)
    print("... all done. Hopefully to your satisfaction?")
