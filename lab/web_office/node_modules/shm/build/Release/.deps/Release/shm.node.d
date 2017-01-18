cmd_Release/shm.node := ln -f "Release/obj.target/shm.node" "Release/shm.node" 2>/dev/null || (rm -rf "Release/shm.node" && cp -af "Release/obj.target/shm.node" "Release/shm.node")
