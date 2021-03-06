echo "printenv: "
printenv

export CASM_BUILD_DIR=$(pwd)
export CASM_BASH_COMPLETION_DIR=$PREFIX/.bash_completion.d
export CASM_WRITE_BC_SHORTCUT=$PREFIX/.bash_completion
export CASM_PYTHON="python"
export CASM_PREFIX=$PREFIX
export CASM_ZLIB_PREFIX=$CONDA_PREFIX
export CASM_BOOST_PREFIX=$CONDA_PREFIX

. $CASM_BUILD_DIR/build_scripts/install-functions.sh
bash $CASM_BUILD_DIR/build_scripts/install-bash-completion.sh
bash $CASM_BUILD_DIR/build.sh
# pip install --no-cache-dir six
make install
