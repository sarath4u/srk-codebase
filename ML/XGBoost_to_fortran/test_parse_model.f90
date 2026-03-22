program test_parse_model
  use parse_model_mod
  implicit none
  real, allocatable :: X(:,:), preds(:)
  integer :: n_samples, n_features, i

  ! Define test data
  n_samples = 2
  n_features = 3
  allocate(X(n_samples, n_features))
  ! Columns: f2, f0, f1
  X(1,:) = [100.0, 10.0, 500.0]
  X(2,:) = [400.0, 20.0, 1500.0]

  ! Call xgb_predictor
  preds = xgb_predictor("treeModel.txt", 100, 3, X, "base_score.txt")

  ! Print results
  print *, "Predictions:"
  do i = 1, n_samples
    print '(A,I0,A,F12.6)', "Sample ", i, ": ", preds(i)
  end do
end program test_parse_model
