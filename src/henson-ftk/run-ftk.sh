# ftk -f mpas-o-pt --input /nfs/gce/projects/PEDAL-GCE/hguo/data/20210421_sim7_CORE_60to30E2r2/mpas.yaml \
# --output mpas.vtp --ptgeo-seeds 101,49,50,101,-48,-47,1,-1400,-1400 --ptgeo-checkpoint-days 1 \
# --timesteps 4 --geo --accelerator cuda


ftk -f test --input ./ndarray.yaml --output test.vtp --accelerator cuda
