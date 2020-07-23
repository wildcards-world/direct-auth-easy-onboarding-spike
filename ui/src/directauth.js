import TorusSdk from "@toruslabs/torus-direct-web-sdk";

export const createTorusSdk = async () => {
  const torusSdk = new TorusSdk({
    baseUrl: `http://localhost:3000/serviceworker/`,
    enableLogging: true,
    proxyContractAddress: "0x4023d2a0D330bF11426B12C6144Cfb96B7fa6183", // details for test net
    network: "ropsten", // details for test net
  });
  console.log("Before");
  await torusSdk.init({ skipSw: false });
  console.log("After");
  return torusSdk;
};
/*const torusdirectsdk = new TorusSdk({
  baseUrl: `${location.origin}/serviceworker`,
  enableLogging: true,
  proxyContractAddress: "0x4023d2a0D330bF11426B12C6144Cfb96B7fa6183", // details for test net
  network: "ropsten", // details for test net
});
this.torusdirectsdk = torusdirectsdk;



        [GOOGLE]: {
          name: "Google",
          typeOfLogin: "google",
          clientId: "221898609709-obfn3p63741l5333093430j3qeiinaa8.apps.googleusercontent.com",
          verifier: "google-lrc",
        },
*/
