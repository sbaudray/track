type user = {
  username: string,
  email: string,
};

type t =
  | Alien
  | Citizen(user);

type action =
  | Login(user)
  | Logout;
