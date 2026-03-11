{
    description = "Derivation for the poti library";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
        flake-utils.url = "github:numtide/flake-utils";
    };

    outputs = { self, nixpkgs, flake-utils }: flake-utils.lib.eachDefaultSystem (system:
        let
            pkgs = import nixpkgs { inherit system; };
        in
        {
            packages.poti = pkgs.stdenv.mkDerivation (finalAttrs: {
                name = "poti";
                version = "5.0";
                inherit system;

                src = ./.;
                nativeBuildInputs = with pkgs; [ perl cmake ];
                # poti's cmake version is less then 3.5, so i need to tell it do it anyway.
                cmakeFlags = [ "-DCMAKE_POLICY_VERSION_MINIMUM=3.5" ];

                doCheck = true;
            });
            defaultPackage = self.packages.${system}.poti;
            devShells.default = pkgs.mkShell {
                buildInputs = [ self.packages.${system}.poti ];
            };
        }
    );
}
