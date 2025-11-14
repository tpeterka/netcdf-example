program producer
    use mpi
    implicit none

    integer :: ierr
    integer :: rank, size

    ! Initialize MPI
    call MPI_Init(ierr)

    ! Get rank and size
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
    call MPI_Comm_size(MPI_COMM_WORLD, size, ierr)

    ! Print to stderr
    write(0,*) 'producer: comm rank ', rank, ' size ', size

    ! Finalize MPI
    call MPI_Finalize(ierr)

end program producer

