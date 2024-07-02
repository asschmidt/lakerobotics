#!/usr/bin/env fish

set -gx LR_TOP_PATH /home/andreas/Projects/LR/lakerobotics

# Set PATH for Lakerobotics source and build output directories
# They are used as rooth paths for other scripts and build processes
set -gx LR_ROOT_PATH $LR_TOP_PATH

set -gx LRPLATFORM_ROOT_PATH $LR_ROOT_PATH/lrplatform
set -gx LRAPPLICATION_ROOT_PATH $LR_ROOT_PATH/lrapplications

set -gx LRPLATFORM_SOURCE_PATH $LRPLATFORM_ROOT_PATH/src
set -gx LRPLATFORM_BUILD_PATH $LRPLATFORM_ROOT_PATH/out

set -gx LRAPPLICATION_SOURCE_PATH $LRAPPLICATION_ROOT_PATH/src
set -gx LRAPPLICATION_BUILD_PATH $LRAPPLICATION_ROOT_PATH/out

#set -gx LRPLATFORM_ROOT_PATH /home/andreas/Projects/LR/lakerobotics/lrplatform
#set -gx LRAPPLICATION_ROOT_PATH /home/andreas/Projects/LR/lakerobotics/lrapplication

fish