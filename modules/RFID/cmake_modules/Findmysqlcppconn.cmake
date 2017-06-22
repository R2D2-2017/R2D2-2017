include(LibFindMacros)
# Use pkg-config to get hints about pathsdd
libfind_pkg_check_modules(mysqlcppconn_PKGCONF mysqlcppconn)

find_path(mysqlcppconn_INCLUDE_DIR
  NAMES sqlstring.h
  prepared_statement.h
  PATHS ${mysqlcppconn_PKGCONF_INCLUDE_DIRS}
)

find_library(mysqlcppconn_LIBRARIES
  NAMES mysqlcppconn
  PATHS ${mysqlcppconn_PKGCONF_LIBRARY_DIRS}
)
